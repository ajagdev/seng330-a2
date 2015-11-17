#include <iostream>
#include <vector>
#include <fstream>
#include <boost/serialization/vector.hpp> 
#include <boost/archive/text_oarchive.hpp> 
#include <boost/archive/text_iarchive.hpp> 


//item base class

class GymItem {
public:
   virtual GymItem* clone() = 0;
   virtual void start_machine() = 0;
   virtual void serialize() = 0;

};


//item prototype factory

class Factory {
public:

   //makes gym machine
   static GymItem* make_machine(int choice);

private:

   //different GymItem probabality
   static GymItem* gym_protos[3];
};

int main() {

   std::vector <GymItem*> gymItems;
   int choice;

 // restore from saved data and print to verify contents  
    {  
        // xreate and input archive  
        std::ifstream ifs( "gymItemsCreated.dat" );  
        boost::archive::text_iarchive ar( ifs );  
        ar & gymItems;
   }

   // user select gym items to build
   while (true) {
    
      std::cout << "\n\nEnter a value... \n Treadmill(1)\n Stationary Bike(2)\n End(0): ";
      std::cin >> choice;
    
      if (choice != 1 && choice != 2) {
        break;
      }gymItems.push_back(
         Factory::make_machine(choice)
         );
	}

   for (int i=0; i < gymItems.size(); ++i) {
      gymItems[i]->start_machine();
   }
   
      // save data
    {  
      std::ofstream ofs( "gymItemsCreated.dat" );  
      boost::archive::text_oarchive ar(ofs);  
      ar & gymItems;
    } 

   //clear the vector
   for (int i=0; i < gymItems.size(); ++i) {
      delete gymItems[i];
   }
}


//Treadmill class
class Treadmill : public GymItem {
public:
   GymItem* clone() { 
   return new Treadmill; 
   }
   int currentSpeed = 0;
   int goalSpeed = 0;
   void start_machine() {
      std::cout << "Treadmill starting up. Hold on to your love handles\n"; 
      currentSpeed = 1;
      goalSpeed = 10;
   }
   void serialize(){
   }
};

//bike class
class StationaryBike : public GymItem {
public:
   GymItem* clone() { 
   return new StationaryBike; 
   }
   int currentSpeed = 0;
   int goalSpeed = 0;
   int seatHeight = 0;
   void start_machine() {
      std::cout << "Stationary Bike starting up. Press + to increase resistance \n"; 
      currentSpeed = 1;
      goalSpeed = 10;
      seatHeight = 5;
   }
   void serialize(){
   }
};


GymItem* Factory::gym_protos[] = {
   0, new Treadmill, new StationaryBike
};

GymItem* Factory::make_machine(int choice) {
   return gym_protos[choice]->clone();
}