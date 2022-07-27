#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>
using namespace std;




//FOR A SINGLE PERSON:

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

    


};







//FOR A WHOLE POPULATION:


class Population 
{

int n_people;
double prob;

public:

    //make population array:
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



    // represent the status in terms of integers:
    // 0=suspetable
    // 1=sick
    // 2=recovered
    // 3=vaccinated

    void random_infection(int array_name[]) {
        //remeber to include `srand(time(nullptr));` (seed) before executing this func in main

        int rand_no = rand()%((0 - n_people) + 1); //generate random number between 0 and pop. no.


        if (array_name[rand_no] == 0) // only infect if suseptable (recovered people (i.e. 2) have immunity -- will be used later on too)
        {
            array_name[rand_no] = 1; //the random poerson is infected in the population
        }
    }




    //adapted from online:
    int count_infected(int array_name[], int no_elements) {
        /* checks array a for number of occurrances of value */
        
        int i, count = 0;

        for (i = 0; i<no_elements; i++) {
            if (array_name[i] == 1) { //if values in the pop array are 1 (ie infected)
                ++count; /* it was found */
                }
        }
        
        return count;
        
    }

    //set transfer probability:
    float transf_prob(float probability) {
        prob = probability;
     

        //probibilty is equivilant to the R-rate?


        return prob;


    }


    //set a certain number of people to be vaxxed
    void vax(int array_name[], int vax_no) {

        int rand_no = rand()%((0 - n_people) + 1); //generate random number between 0 and pop. no.

        for(int i=0; i<vax_no; i++) //vax `vax_no` number of people
        {
            if (array_name[rand_no] == 0) // only vax if suseptable (recovered people (i.e. 2) have immunity -- will be used later on too)
            {
                array_name[rand_no] = 3; //the random poerson is vaxxed in the population
            }
        }
    }


    
};








int main() {
    



    //FOR A SINGLE PERSON:
    
    Person joe;

    srand(time(nullptr)); //seed the random number 
    int step = 1; //how many days to follow patient until recovered

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
    







    //FOR A WHOLE POPULATION:

    Population population;

    int n = 1000; //number of people
    int* ptr = population.population(n); //make into a pointer in order to print the array and use it in other functions


    //set the number of vaxxed:
    population.vax(ptr, 0); //0 random people vaxxed (assume no vax available)
 



    srand(time(nullptr)); //seed random number `rand_no` for function below


    //loop infection for many days:
    for (int day =1; day<1000000000 ; day++) { 


        float bad_luck = (float) rand()/(float)RAND_MAX; //random generation of number between 0 and 1 
        //(can use in any proj btw)

        //random infection:
        if (bad_luck>.95) { 
            population.random_infection(ptr);
            //const int day_beg = day;
        }




        //loop for all elements in pop array:
        for (int i = 0; i < n; i++) {    
            if (ptr[i]==1) //find 1s
            {   
                
                float rand_no = (float) rand()/(float)RAND_MAX; //seperate random generation of number between 0 and 1
                float prob = population.transf_prob(0.6); //transfer prob is 0.4

                //condition to infect nearest neighbours of already infected person:
                if (rand_no>prob){
                    if (ptr[i-1] == 0 ) {
                        ptr[i-1] = 1;
                    }
                    
                    if (ptr[i+1] == 0 ) {
                        ptr[i+1] = 1;
                    }
                }

                //infect 4 random people that the already infected person comes in contact with:
                for (int k=0; k < 4; k++){
                    int rnd = rand()%((0 - n) + 1); //generate random number between 0 and n

                    //generate random no after each loop iteration:
                    float rnd_float = (float) rand()/(float)RAND_MAX; //seperate random generation of number between 0 and 1
                    
                    if (rnd_float>prob) //condition to infect people in contact
                    {
                        if (ptr[rnd] == 0 ) {
                            ptr[rnd] = 1;
                        }
                    }
                }




                
                for (int j=2; j>0; j--){
        
                    //problem: the above infections are not "allowed" to recover during the recovery of one
                    
                    cout << "On day " << day++ << ", there are " << population.count_infected(ptr, n) << " poeple infected\n";  
                }
           


               /*
                const int day_beg = day;  


                
                if (day_beg == day - 5){
                    ptr[i] = 2;
                }
                */

                ptr[i] = 2;

                //cout<< day_beg << " " << day << "\n";  


                //maybe add the if =2 into a seperate loop and then join ting

        
            }

        }



        //printing no of people infected and the corresponding day:
        cout << "On day " << day << ", there are " << population.count_infected(ptr, n) << " poeple infected\n";



        
        
        //break condition:s
        if (day>30 && population.count_infected(ptr, n)==0) {
            break;
        }


    }
    


}