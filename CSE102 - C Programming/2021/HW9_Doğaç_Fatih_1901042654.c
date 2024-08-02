#include <stdio.h>
#include <string.h>

#define MAX_PEOPLE 15
#define MAX_QUEUE 5

/*
*	Because the max customer number is 50, I created 5 queues with 15 empty spot each of them.
*	That means 75 customer can be in the system.
*
*	Current sequence prints all queues.
*
*	The 2D array with name "a" stands for customers , all queues.
*	
*	Bugs:
*	When the sequence is 0-0-0-0-0-1-1-0 , if the new customer with 2 label arrives,
*	New sequence will be 0-0-0-0-0-1-1-2-0 . Which is wrong. It should be 0-0-0-0-0-1-1-0-2
*	
*	Fatih Doğaç 1901042654
*/


typedef struct{
    char name[MAX_PEOPLE];
    int age;
    int label;
}Customer;

int where_to_add(Customer customers[MAX_QUEUE][MAX_PEOPLE]  , Customer c1);
void initialize_queue(Customer a[MAX_QUEUE][MAX_PEOPLE]);
void print_queue(Customer a[MAX_QUEUE][MAX_PEOPLE]);
void process(Customer a[MAX_QUEUE][MAX_PEOPLE]);
void add_to_queue(Customer customers[MAX_QUEUE][MAX_PEOPLE] , Customer c1);
void menu();

void main(void){
	menu();
}
void menu(){

	Customer customers[MAX_QUEUE][MAX_PEOPLE];

	int choice = 0;

	initialize_queue(customers);

	while(choice != 3){
		printf("\n***********Banking System***********\n");
		printf("Current sequence: ");
		print_queue(customers);
		printf("\n1- Add customer\n");
		printf("2- Process customer\n");
		printf("3- Exit\n");

		scanf("%d",&choice);

		switch(choice){
			case 1:
				printf("\nPlease enter the name of customer: \n");
				char name[20];
				scanf("%s",name);

				printf("\nPlease enter the age of customer: \n");
				int age;
				scanf("%d",&age);

				if(age < 6){
					printf("Bad input\n");
					break;
				}

				printf("\nPlease enter the label of customer: \n");
				int label;
				scanf("%d",&label);

				if(label < 0 || label > 4){
					printf("Bad input\n");
					break;
				}

				Customer c;
				strcpy(c.name,name);
				c.age = age;
				c.label = label;

				add_to_queue(customers , c);
				break;
			case 2:
				process(customers);
				break;
			case 3:
				break;
			default:
				printf("This is not an option. Try again.\n");
				break;
		}
	}
}
void initialize_queue(Customer a[MAX_QUEUE][MAX_PEOPLE]){ // Initializing the array.

    for(int i = 0; i<MAX_QUEUE; i++){
        for(int j = 0; j<MAX_PEOPLE; j++){		// -1 on the label means this spot is empty.
            a[i][j].label = -1;
        }
    }
}
void process(Customer a[MAX_QUEUE][MAX_PEOPLE]){
    int counter = 0;

    for(int j = 0; j< MAX_PEOPLE; j++){ // How many non-empty spots in the array.
            
        if(a[0][j].label != -1){
            counter++;
        }
    }

    if(counter == 1){ // After the process , this queue will be replaced by next queue. Because there will be nobody in that queue.

    	printf("\nProceed customer is %s\n" , a[0][0].name);
        Customer hold[MAX_QUEUE][MAX_PEOPLE];
        initialize_queue(hold);

        /* I didn't use a loop because in the pdf it was stated that max number will be 50. */
        memcpy(hold[0] , a[1] , MAX_PEOPLE * sizeof(Customer)); // Making the second queue the first queue
        memcpy(hold[1] , a[2] , MAX_PEOPLE * sizeof(Customer)); // Because first queue will be empty after the process.
        memcpy(hold[2] , a[3] , MAX_PEOPLE * sizeof(Customer));
        memcpy(hold[3] , a[4] , MAX_PEOPLE * sizeof(Customer));

        memcpy(a[0] , hold[0] , MAX_PEOPLE * sizeof(Customer)); // Updating the main queue.
        memcpy(a[1] , hold[1] , MAX_PEOPLE * sizeof(Customer));
        memcpy(a[2] , hold[2] , MAX_PEOPLE * sizeof(Customer));
        memcpy(a[3] , hold[3] , MAX_PEOPLE * sizeof(Customer));
        memcpy(a[4] , hold[4] , MAX_PEOPLE * sizeof(Customer));

    }
    else if(counter==0){
        printf("There is no customer in the queue.\n");
    }
    else{ // The queue has more than one person.

    	printf("\nProceed customer is %s\n", a[0][0].name);

    	for(int i = 0; i< MAX_PEOPLE - 1; i++){
            	
            a[0][i] = a[0][i+1]; // Deleting the first person and shifting the queue to the left.
		    
    	}
    	a[0][MAX_PEOPLE - 1].label = -1; // Deleting the buffer.
    }
}
void print_queue(Customer a[MAX_QUEUE][MAX_PEOPLE]){
    int i = 0 , j =0 , flag = 1;

    for(i = 0;i<MAX_QUEUE; i++){
        for(j = 0; j<MAX_PEOPLE; j++){
            if(a[i][j].label != -1){
                printf("%d",a[i][j].label);	// First person.
                flag = 0;
                j++;
                break;
            }
        }
        if(flag == 0){
            break;
        }
    }

    for(int k = i; k<MAX_QUEUE; k++){

        for(j; j<MAX_PEOPLE; j++){

            if(a[k][j].label != -1){
                printf("-%d",a[k][j].label); // And the others. I did that because of dashes (-).
            }
        }
        j = 0;      
    }
    printf("\n");
    
}
void add_to_queue(Customer customers[MAX_QUEUE][MAX_PEOPLE] , Customer c1){

	int index = where_to_add(customers , c1) , flag = 1 , hold;

	for(int i = 0; i< MAX_PEOPLE; i++){

		if(customers[index][i].label == c1.label && customers[index][i+1].label != c1.label){ 
			// The person's label after i'th person is not the same. So new customer c1 will be located here.

			for(int j = MAX_PEOPLE -1; j>i + 1; j--){ // Shifting the queue to the right.

				customers[index][j] = customers[index][j-1];

			}

			customers[index][i+1] = c1; // Adding the new customer.
			return;
		}

		else if(customers[index][0].label == -1){ // This queue is empty.
			customers[index][0] = c1;
			return;
		}
		else if(customers[index][i].label == c1.label){ // Is there any other person with the same label. ?
			flag = 0; // Yes. 
		}
		
	}

	if(flag == 1){ // No. The queue is not empty but there is no one else with the label of customer c1 

		for(int i = 0; i<MAX_PEOPLE; i++){

			if(customers[index][i].label > c1.label){ // Locating the label's position.
				hold = i;
				break;
			}
			else if(customers[index][i].label == -1){
				customers[index][i] = c1;
				return;
			}
		}

		for(int i = MAX_PEOPLE - 1; i> hold + 1; i--){ // Shifting the queue to the right.

			customers[index][i] = customers[index][i-1];
		}

		customers[index][hold + 1] = c1;
		return;
	}
}
/** returns the queue which is the customer c1 will be added. */
int where_to_add(Customer customers[MAX_QUEUE][MAX_PEOPLE] , Customer c1){

    int max , counter = 0 , returnValue = 0; // returnValue is the to be returned queue's index.

    switch (c1.label)
    {
    case 0:
        max = 5;
        break;
    case 1:
        max = 3;
        break;
    case 2:
        max = 3;
        break;
    case 3:
        max = 2;
        break;
    case 4:
        max = 2;
        break;
    }

    for(int i =0; i<MAX_QUEUE; i++){
        for(int j =0; j<MAX_PEOPLE; j++){

            if(customers[i][j].label == c1.label){
                counter++;
                if(customers[i][j+1].label != c1.label){ // Counting the current customers with same label.
                    break;
                }
            }
        }

        if(counter < max){ // If there is space in that queue.
            return returnValue;
        }
        // If not.
        returnValue++;
        counter = 0;
                
    }


}