#include "msrUtils.h"
#include "modemUtils.h"
#include "keyboardUtils.h"
#include <loggerUtils.h>
#include "system_errors_loggerUtils.h"

//#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */
#include <pthread.h>          /*  for threading             */
#include <sys/ioctl.h>

#define MAX_LINE          1000
#define port              6000

eTestResult compareData( uint8* _sentBytes, uint8* _receivedBytes, int sentBytes, int receivedBytes )
{
    if( receivedBytes != sentBytes )
    {
        LOG("Received data length not match: received %d sent %d", \
        receivedBytes, \
        sentBytes );
        if( !TEST_EQ( OS_ModemDisconnect( ), OS_OK ))
        {
            LOG( "Unable to disconnect from line" );
            return SYS_FAIL;
        }
    }

    for( int i = 0; i <= sentBytes-1; i++ )
    {
        if( _receivedBytes[ i ] != _sentBytes[ i ] )
        {
            LOG( "The buffers are not similar\n" );
            if( !TEST_EQ( OS_ModemDisconnect( ), OS_OK ))
            {
                LOG( "Unable to disconnect from line" );
                return SYS_FAIL;
            }
        }
    }

    LOG( "The buffers are similar\n" );
    return SYS_PASS;
}

eSqaBoolean fillBuffer( uint8* _buffer, uint32 _bufferLength )
{
    uint32 i;
    LOG( "Filling the buffer\n" );
    for( i = 0; i < _bufferLength; i++ )
    {
        _buffer[ i ] = '0';
    }
    return SYS_TRUE;
}
/*
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];

    //Send some messages to the client
    message = "Greetings! I am your connection handler\n";
    write(sock , message , strlen(message));

    message = "Now type something and i shall repeat what you type \n";
    write(sock , message , strlen(message));

    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        write(sock , client_message , strlen(client_message));
    }

    if( read_size == 0 )
    {
        puts( "Client disconnected" );
        fflush( stdout );
    }
    else if( read_size == -1 )
    {
        LOG( "recv failed" );
    }

    //Free the socket pointer
    free(socket_desc);

    return 0;
}*/

eSqaBoolean readLine(int sockd, void *vptr, int maxlen)
{
    int n, rc;
    char    c, *buffer;

    buffer = (char*)vptr;

    LOG("read()");
    for( n = 1; n < maxlen; n++ )
    {
        if( (rc = read(sockd, &c, 1)) == 1 )
        {
            *buffer++ = c;
            if ( c == '\n' )
            {
                break;
            }
        }
        else if( rc == 0 )
        {
            if ( n == 1 )
            {
                LOG("Empty line..");
                return SYS_TRUE;
            }
            else
                break;
        }
        else
        {
            LOG("Error. read() return -1");
            return SYS_FALSE;
        }
    }

    *buffer = 0;
    return SYS_TRUE;
}

eSqaBoolean writeLine(int sockd, const void *vptr, int n)
{
    int nwritten;
    const char *buffer;

    buffer = (char*)vptr;

    LOG("write()");
    while ( n > 0 )
    {
        if ( (nwritten = write(sockd, buffer, n)) <= 0 )
        {
            if ( nwritten == -1 )
            {
                LOG("Error. write() return -1");
                return SYS_FALSE;
            }
            else
                nwritten = 0;
        }

    n  -= nwritten;
    buffer += nwritten;
    }

    return SYS_TRUE;
}

eTestResult template_custom_001( void )
{
    stMsrTracksSampleGen check_sample;

    if (msrUtils_InitRoutine(SYS_TRUE, SYS_TRUE) != SYS_OK)
    {
        LOG("Error: MSR initialization failed...\n");
        return SYS_FAIL;
    }

    LOG("********************ASCII_DATA********************************\n");

    memset(&check_sample, 0, sizeof(stMsrTracksSampleGen));

    if (msrUtils_CreateCheckSampleGen(&check_sample) != SYS_OK)
    {
        LOG("Error: check sample not created\n");
        return SYS_FAIL;
    }

    LOG("Data on card:\ntrack_1: %s\ntrack_2: %s\ntrack_3: %s\n",
    check_sample.m_ascii.m_track1, check_sample.m_ascii.m_track2, check_sample.m_ascii.m_track3 );

    LOG("Trying to flush card data...");
    if( msrUtils_Flush() != SYS_OK )
    {
        return SYS_FAIL;
    }
    LOG("Done");

    return SYS_PASS;
}

eTestResult modemDialTest( void )
{
    const int testDataLength = 512;
    uint8 testData[testDataLength];
    uint8 receivedData[testDataLength];
    uint16 receivedDataLength;

    BOOLEAN exit = FALSE;
    uint8* i_phoneNumber;
    int iTimeout = 60000;
    MAGIC_KEY_TYPE key;
    OS_STATUS status;

    if (keyboardUtils_Flush() != SYS_OK)
    {
        LOG("Error: keyboard flush failed");
        return SYS_FAIL;
    }

    while( exit == FALSE )
    {
        LOG("Press:  1 - 229 | 2 - 231 | 3 - 232 ");

        status = OS_KeybdRestrictedGet( &key, 600000 );

        if( status == OS_OK )
        {
            if( key == MAGIC_KEY_1 )
            {
                i_phoneNumber = "229";
                exit = TRUE;
            }

            if( key == MAGIC_KEY_2 )
            {
                i_phoneNumber = "231";
                exit = TRUE;
            }

            if( key == MAGIC_KEY_3 )
            {
                i_phoneNumber = "232";
                exit = TRUE;
            }

            if( key == MAGIC_KEY_CANCEL )
                exit = TRUE;

            if ( (key != MAGIC_KEY_CANCEL) &&
                (key != MAGIC_KEY_1) &&
                (key != MAGIC_KEY_2) &&
                (key != MAGIC_KEY_3) )
            {
                LOG("\n");
                LOG("Error: wrong input, try again");
                exit = FALSE;
            }
        }
    }

    LOG( "Initializing modem with 'NULL' parameters" );
    if( !TEST_EQ( OS_ModemInit( NULL ), OS_OK ) )
    {
        LOG( "Unable to initialize modem" );
        if( !TEST_EQ( OS_ModemDisconnect( ), OS_OK ))
        {
            LOG( "Unable to disconnect from line" );
        }
        return SYS_FAIL;
    }
    LOG( "Done\n" );

    LOG( "Trying to dial, number - %s", i_phoneNumber );
    if( !TEST_EQ( OS_ModemDial( i_phoneNumber , strlen(i_phoneNumber), DIAL_TONE, iTimeout ), OS_OK ))
    {
        LOG( "Unable to perform dial" );
        if( !TEST_EQ( OS_ModemDisconnect( ), OS_OK ))
        {
            LOG( "Unable to disconnect from line" );
        }
        return SYS_FAIL;
    }
    LOG( "Done\n" );

    LOG( "Trying to get modem status" );
    if( !TEST_EQ( OS_ModemStatus( iTimeout ), OS_MOD_CONNECTED ))
    {
        LOG( "Unable to get modem status");
        if( !TEST_EQ( OS_ModemDisconnect( ), OS_OK ))
        {
            LOG( "Unable to disconnect from line" );
        }
        return SYS_FAIL;
    }
    LOG( "Status: OS_MOD_CONNECTED\n" );

    modemUtils_SkipDataBeginning( );
/*
    if( !TEST_EQ(OS_ModemFlush( READ_AND_WRITE_BUFFERS ), OS_OK))
    {
    LOG("Unable to flush TxRx buffers");
    TEST_EQ(OS_ModemDisconnect(), OS_OK);
    return SYS_FAIL;
    }
    LOG("Read/write buffers flushed");
*/
    fillBuffer( testData, testDataLength );
    LOG( "Done" );

    LOG( "Trying to send %d bytes \n", testDataLength );

    if( !TEST_EQ( OS_ModemSend(testData, testDataLength), OS_OK ))
    {
        LOG( "Unable to sent data" );
        if( !TEST_EQ( OS_ModemDisconnect( ), OS_OK ))
        {
            LOG( "Unable to disconnect from line" );
        }
        return SYS_FAIL;
    }
    LOG( "Done" );

    LOG( "Trying to receive data" );
    if( !TEST_EQ(OS_ModemReceive( receivedData, testDataLength, &receivedDataLength, iTimeout, iTimeout ), OS_OK ))
    {
        LOG( "Disconnecting from remote peer" );
        if( !TEST_EQ(OS_ModemDisconnect( ), OS_OK ))
        {
            LOG( "Unable to disconnect from line" );
        }
        return SYS_FAIL;
    }
    LOG( "Done" );

    LOG( "Received %d bytes", receivedDataLength );

    LOG( "Checking received data" );
    compareData( testData, receivedData, testDataLength, receivedDataLength );

    LOG( "Disconnecting" );
    if( !TEST_EQ(OS_ModemDisconnect( ), OS_OK ))
    {
        LOG( "Unable to disconnect from line" );
        return SYS_FAIL;
    }
    LOG( "Modem has disconnected\n" );

    LOG( "Trying to stop modem" );
    if( !TEST_EQ( OS_ModemStop( ), OS_OK ))
    {
        return SYS_FAIL;
    }

    return SYS_PASS;
}

eTestResult simpleEchoServTest( void )
{
    //BOOLEAN flag = FALSE;
    int       list_s, conn_s;
    struct    sockaddr_in servaddr;//, client_address;
    //char      buffer[ MAX_LINE ];
    //int       *new_sock;
    fd_set readfds, testfds;
    int fin = 0;

    LOG( "Creating the listening socket" );
    if( ( list_s = socket(AF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
        LOG( "Error creating listening socket" );
        return SYS_FAIL;
    }
    LOG( "Done" );

    /*  Set all bytes in socket address structure to zero  */
    memset( &servaddr, 0, sizeof( servaddr ) );
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
    servaddr.sin_port        = htons( port );

    LOG( "Bind socket address to the listening socket.." );
    if ( bind(list_s, ( struct sockaddr * ) &servaddr, sizeof( servaddr ) ) < 0 )
    {
        LOG( "Error calling bind" );
        return SYS_FAIL;
    }
    LOG( "Done" );

    LOG( "Listening.." );
    if ( listen( list_s, 2 ) < 0 )
    {
        LOG( "Error calling listen()" );
        return SYS_FAIL;
    }
    LOG( "Done" );

    FD_ZERO(&readfds);
    FD_SET(list_s, &readfds);

    while( fin != 6 )
    {
        char ch[ MAX_LINE ];
        int fd, result;
        int nread;
        testfds = readfds;
        //int client_len;

        LOG( "Waiting for a connection" );

        //result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *) 0);
        result = select(FD_SETSIZE, &testfds, NULL, NULL, NULL);
        if( result < 1 )
        {
            LOG( "Problem with select" );
            return SYS_FAIL;
        }

        for( fd = 0; fd < FD_SETSIZE; fd++ )
        {
            if( FD_ISSET( fd,&testfds ))
            {
                LOG( "fd = %d \t\t list_s =%d", fd, list_s );
                if( fd == list_s )
                {
                    if( ( conn_s = accept( list_s, NULL, NULL )) < 0 )
                    {
                        LOG( "Error calling accept()" );
                        return SYS_FAIL;
                    }

                    FD_SET( conn_s, &readfds );
                    LOG("-------------- new client --------------");
                    LOG( "Adding client on fd %d", conn_s );
                }
                else
                {
                    LOG("fd = %d \t\t nread = %d", fd, nread );
                    ioctl( fd, FIONREAD, &nread);
                    if(nread == 0)
                    {
                        close( fd );
                        FD_CLR( fd, &readfds );
                        LOG( "Removing client on fd %d\n", fd );
                    }
                    else
                    {
                        readLine( fd, ch, MAX_LINE-1 );
                        sleep(5);
                        LOG("Serving client on fd %d\n", fd);
                        writeLine( fd, ch, strlen( ch ) );
                    }
                }
            }
        }
        fin++;
    }
 /*       if( ( conn_s = accept( list_s, NULL, NULL ) ) < 0 )
        {
            LOG( "Error calling accept()" );
            return SYS_FAIL;
        }
        LOG( "Done" );

        pthread_t sniffer_thread;
        new_sock = ( int* )malloc ( 1 );
        *new_sock = conn_s;

        LOG( "123" );
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , ( void* ) new_sock) < 0)
        {
            LOG( "Could not create thread" );
            return SYS_FAIL;
        }
        LOG( "321" );


        readLine( conn_s, buffer, MAX_LINE-1 );
        writeLine( conn_s, buffer, strlen( buffer ) );

        flag = TRUE;

        LOG( "Trying to close socket" );
        if ( close(conn_s) < 0 )
        {
            LOG( "Error calling close()" );
            return SYS_FAIL;
        }
        LOG( "Done" );
    }*/

    return SYS_PASS;
}
