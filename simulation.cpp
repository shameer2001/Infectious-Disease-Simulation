#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;


class Person {
    
private:

int n = 2001; //number infected days MINUS 1 (its bc of the for loop and if statements in main() for Person joe)
//set a default value before assignment by infect() so that first conditional in status_string() works
//(otherwise its the same n==0 condition is the same as "recovered" conditional)



public: 

    void infect(int n_dummy) { //you decide how many days of infection there are
        n=n_dummy; //also make private n usable in this sectoin?
    }

    /*void acc_infect() {
        --n;
        cout << n;
    }*/

    /*
    void lol() {
        cout << n;
    }*/
    
    void update() { //update the days after infection by counting down
        n--;   //takes 1 away from n 
    }



    
    bool is_stable() { //is the "patient" stable?
      
        if (n<1) { 
            return true;  //if the days left of infection are 0 then patient is stable
        }
        
        if (n>0) {
            return false; //if days left of infection then not stable
        }
    }

    string vax_yn; //string variable that will be assigned a y or n if patient is vaxxed or not
    //(will be assigned in main() )
    
    
    
    string status_string() {

        if (n==2001) {
            return "suseptable";
        }  //if n is the default value (before assignment by infect() )... then patient is still sus
        
        if (is_stable()==false) {
            return "sick";
        }
        
        if (is_stable()==true) {
            return "recovered";
        }
        
        if (vax_yn=="y") {
            return "vaccinated";
        }
        
    }

    //for later:
    // 0=suspetable
    // 1=sick
    // 1=recovered
    // 3=vaccinated


};



class Population {

int n_people;

public:

    
    int* population(int npeople) //included * to return an array
    {
        n_people = npeople;
        int* pop = new int[n_people]; //include to return an array + create an array representing the population


        //for loop to make all values in array 0 (suspetable)
        for(int i=0; i<n_people; i++) {
            pop[i] =0;
        }

        return pop;
    }


    

    void random_infection(int array_name[]) {
        //remeber to include `srand(time(nullptr));` (seed) before executing this func in main

        int rand_no = rand()%((0 - n_people) + 1); //generate random number between 0 and pop. no.

        array_name[rand_no] = 1; //the random poerson is infected in the population
        
        Person rand_person;
        rand_person.infect(5); //assume disease is equally deadly for every1 (lasts 5 days for every1)
    }





    int count_infected(int array_name[], int no_elements) {
        //adapted from online:
        /* checks array a for number of occurrances of value */
        
        int i, count = 0;

        for (i = 0; i<no_elements; i++) {
            if (array_name[i] == 1) { //if values in the pop array are 1 (ie infected)
                ++count; /* it was found */
                }
        }
        
        return count;
        
    }




    /*void update() {
        Person rand_person;
        rand_person.n--;
    }
    */
    


    
};


/*
Population::population(int npeople) {
    n_people = npeople;
    int pop[n_people] = {0}; //create an array representing the population

}*/





int main() {
    
    /*
    Person me;
    cout << me.status_string();


    me.infect(5);
    cout << me.status_string();

    me.update();
    cout << me.status_string();

    me.update();
    cout << me.status_string();

    me.update();
    cout << me.status_string();

    me.update();
    cout << me.status_string();

    me.update();
    

    
    me.vax_yn = "y";
    
    
    cout << me.status_string();
    */



    
    /*int n=5;

    while (n>0) {
        --n;
        cout<< n;
    }*/

    /*int a;
    cout <<a;*/

    
    

    Person joe;

    srand(time(nullptr)); //seed the random number (SEARCH WHAT THIS MEANS AND WHY YOU CAN ONLY CALL THIS ONCE AND WHY YOU HAVE TO CALL THE RAND AGAIN AND AGAIN (LOOP) OTHER WISE IT ONLY GIVES ~SAME NO.)
    int step = 1; //how many to follow patient until recovered

    for (step; step<100 ; step++) { //start at day 1 and end at 99 with 1 step increments 
        
        

        float bad_luck = (float) rand()/(float)RAND_MAX; //random generation of number between 0 and 1 
        //(can use in any proj btw)
        
        if (bad_luck>.95) { 
            joe.infect(5); //infect joe for 4 days (not 5 bc of the for loop i think)
            for (int i=5; i>0; i--) { 
                joe.update();
                cout << "On day " << step++ << ", Joe is " << joe.status_string() << "\n";

            }//loop the update and status_string for the last 5 days otherwise joe will 
            //remain sick forever 
            //(see how by removing for loop and just include joe.update() under joe.infect(5) )

            if (joe.is_stable()==true) {
            break;
        }
        
        }

        
        



        //cout << bad_luck;
        cout << "On day " << step << ", Joe is " << joe.status_string() << "\n";
        

        if (joe.is_stable()==true) {
            break;
        }
        

    
    }
    






    Population population;
    
    int* ptr = population.population(10); //make into a pointer in order to print the array and use it in other functions

 

    srand(time(nullptr)); //seed random number `rand_no` for function below
    population.random_infection(ptr);
    population.random_infection(ptr);

   
    
    for (int i = 0; i < 10; i++) {    
        cout << "\n" << ptr[i];
    }

    




    


}