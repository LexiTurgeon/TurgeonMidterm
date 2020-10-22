#include<iostream>
#include<fstream>
#include<string>
#include <unistd.h>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
   if(argc!=3){
	cout << "Usage is makeLED and one of: " << endl;
        cout << "on, off, flash, blink or status" << endl;
	cout << "e.g. makeLED flash" << endl;
        return 3;
   }
   string cmd(argv[1]);
   cout << "Starting the makeLED-HW5 program" << endl;
   cout << "The current LED Path is: " << LED3_PATH << endl;

   int n = atoi(argv[2]);

   // select whether command is on, off, flash or status
   if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (cmd=="status"){
	// display the current trigger details
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }
   else if(cmd =="blink"){
	cout << "Blinking the LED " << n << "times" << endl;
	int i;
	for(i=0; i < n; i++){
		writeLED("/brightness", "1");
		sleep(1);
		writeLED("/brightness", "0");
		sleep(1);
	}
   }
   else if(cmd == "toggle"){
	std::fstream fs;
	fs.open(LED3_PATH "/brightness", std::fstream::in);
	string ledStatus;
	while(getline(fs,ledStatus)) cout << ledStatus << endl;
	
	if(ledStatus == "1"){
		writeLED("/brightness","0");
		sleep(1);
        }else if(ledStatus == "0")
		writeLED("/brightness","1");
		sleep(1);
		}
   }

  else{
	cout << "Invalid command!" << endl;
   }
   cout << "Finished the makeLED Program" << endl;
   return 0;
}
