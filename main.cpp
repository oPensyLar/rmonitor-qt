
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QTime>
#include <QCoreApplication>
#include "openmonitorrig.h"
#include "openserial.h"

#define FORMULA_IP "3.3.3.185"
#define PREMIUM_IP "3.3.3.13"



int GetRandomNo(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}


/*  
 *   Senales que se le envia por serial al Arduino
 *
 *   
 *   51 == 3
 *   PowerOn ASUS Premium 
 *   
 *   
 *   
 *   50 == 2
 *   PowerOn ASUS ROG Formula
 *   
 *   
 *   
 *   49 == 0
 *   PowerOff PowerOn relayAsusPremium
 *   
 *   
 *   
 *   
 *   49 == 1
 *   PowerOff PowerOn ASUS ROG Crossair Formula
 *   
 *   
 *   
 */


int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    QString portNam = "/dev/arduinor3";
    oPenSerial serial;
    QStringList listDevs;
    QString strTmp;

    listDevs << "/dev/arduinor3" << "/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0";


    for(int i = 0; listDevs.size() > i; i++)
    {

    	//qDebug() << listDevs.at(i);


		QThread::sleep(2);


		serial.SetPort(listDevs.at(i));



	    if(serial.OpenDev() != 0)
	    {

/*	    	qDebug() << "[!] " << serial.strErr << "\r\n";

	    	if( (listDevs.size() -1) ==i )
	    	{
	    		i = 0;
	    	}

	    	continue;
*/
	    }


	    serial.signal = 5;
	    
	    if(serial.SendSignal()!=0)
	    {
	    	qDebug() << "[!] No response device " << listDevs.at(i);
	    	continue;
	    }

	    	else
	    	{

	    		strTmp = serial.inputSerial;

				if(strTmp.compare("OK\r\n")==0)
				{
	    			qDebug() << "[+] Device found over" << listDevs.at(i);
			    	break;
				}
				break;
	    	}


	    serial.CloseDev();

    }


    oPenMonitorHost OneHost;
    QVector<oPenMonitorHost *> monitor;



    
    monitor << new oPenMonitorHost();

    monitor.at(0)->host = FORMULA_IP;
    monitor.at(0)->port = 22;


    monitor << new oPenMonitorHost();

    monitor.at(1)->host = PREMIUM_IP;
    monitor.at(1)->port = 3389;


/*


    monitor.at(1)->host = PREMIUM_IP;
    monitor.at(1)->port = 3389;    



	monitor << new oPenMonitorHost();
    monitor.at(1)->host = "192.168.1.2";
    monitor.at(1)->port = 3389;

*/


    QTime time = QTime::currentTime();
	qsrand((uint)time.msec());


/*while(1)
{
	qDebug() << GetRandomNo(1, 4);	
}
*/


    int o = 0;
    int status;
	int i;
    //qDebug() << monitor.at(1)->host;


	while(1)
	{
	    for (i = 0; i < monitor.size(); i++)
	    {	    	

	    	//qDebug() << i;
		    //qDebug() << "[+] Connecting " << monitor.at(i)->host << ":" << monitor.at(i)->port;


		    status = monitor.at(i)->CheckStatus();


		    if(status==0)
		    {
				monitor.at(i)->up = true;
		    }


			QThread::sleep(1);

			while(status!=0)
			{


				QThread::sleep(5);


				qDebug() << "[!] Connection host " << monitor.at(i)->host << ":" << monitor.at(i)->port << "(" << monitor.at(i)->errString << ") ... intento numero " << o << "esta UP " << monitor.at(i)->up;


				o++;

				if(o == 80)
				{


					o = 0;

					//Estaba encendida
					if(monitor.at(i)->up)
					{
						qDebug() << "[+] La " << monitor.at(i)->host << " esta colgada? ... Estaba encendida se apagara y luego se encendera .. " << o;


							if(monitor.at(i)->host.compare(FORMULA_IP) == 0)
							{

							    //  48 == 0
							    //  PowerForce ASUS ROG Formula

								serial.signal = 0;
								monitor.at(i)->up = false;

							}	


							if(monitor.at(i)->host.compare(PREMIUM_IP) == 0)
							{


  								//  49 == 1
  								//  PowerForce ASUS Premium
								
								serial.signal = 1;
								monitor.at(i)->up = false;


							}	


					}


						//Estaba apagada
						else
						{


							qDebug() << "[+] La " << monitor.at(i)->host << " estaba apagada.. se encendera .. ";




							if(monitor.at(i)->host.compare(FORMULA_IP) == 0)
							{		

							    //  50 == 2
							    //  Power ASUS ROG Formula

								serial.signal = 2;


							}	




							if(monitor.at(i)->host.compare(PREMIUM_IP) == 0)
							{

  								//  51 == 3
  								//  Power ASUS Premium
								
								serial.signal = 3;								


	      					}


						}	


				    if(serial.SendSignal()==0)
				    {				    	

				    	qDebug() << "[+] Send at " << monitor.at(i)->host << "signal " << serial.signal;
				    	break;
				    }


				}

				}

						

				status = monitor.at(i)->CheckStatus();		


			}



			o = 0;
		}			    

    return a.exec();
}
