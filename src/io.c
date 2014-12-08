/*
 * CSE 2421
 * Fall 2014
 * Lab1
 * 
 * Objectives: Pointers, Dynamic memory allocation, Functions
 * 
 * Author: Damonique Thomas
 */

#include <stdio.h>
#include <stdlib.h>

int numOfDataSets();
double** getsets(double **datasets, int *setsizes, int data_num);
int numInSet(int i);
int chooseSet(double **datasets, int *setsizes, int data_num);
int prompt (double *set, int size, double **datasets, int *setsizes, int data_num);
int min(double *set, int size);
int max(double *set, int size);
int sum(double *set, int size);
int average(double *set, int size);
int sort(double *set, int size);
void quit(double **datasets, int *setsizes, int data_num);

/*
 * Function: main
 * ----------------------------
 * Sets up the dynamically allocated arrays  
 * Ask user for data sets and the numbers in each set
 *
 * returns: 0 on successful completion 
 */
int main(int argc, char**argv) {
    /*Initialize all variables used in main function*/
    int set_num, data_num,i,j,k;
    int *setsizes;
    double **datasets; 
    double input;
    
    data_num = numOfDataSets();
    
    datasets = malloc (data_num*sizeof(double*));
    if (datasets==NULL) {
        printf("Error allocating memory!-datasets\n");
        return 0;
    }
    
    setsizes = malloc (sizeof(int)*data_num);
    if (setsizes==NULL) {
        printf("Error allocating memory!-setsizes\n");
        return 0;
    }   
    
    datasets = getsets(datasets, setsizes, data_num);
    
    k = chooseSet(datasets, setsizes, data_num);
    return 0;
}
/*
 * Function: numOfDataSets
 * ----------------------------
 * Asks user for number of data sets
 *
 * returns: number of data sets 
 */
int numOfDataSets(){
    int data_num;
    printf("Enter the number of data sets: ");
    scanf("%d", &data_num);
    
    return data_num;
}

/*
 * Function: getsets
 * ----------------------------
 * Reads the user input for doubles in the data sets
 *
 * datasets: the pointer to the pointer of doubles 
 * setsizes: the pointer to the sizes of each set
 * data_num: the number of data sets
 * 
 * returns: dynamically alloted array containing data sets  
 */
double** getsets(double **datasets, int *setsizes, int data_num){
    int i, j,set_num;
    double input; 
    
    for(i = 0; i < data_num; i++){
        set_num = numInSet(i);
        *(setsizes +i) = set_num;
        *(datasets+i) = (double*) malloc(set_num*sizeof(double));
        if (*(datasets+i)==NULL) {
            printf("Error allocating memory!-set\n"); //print an error message
            return 0;
        } 
        /*Get floats in each data set*/
        for (j = 0; j < set_num; j++){
            scanf(" %lf", &input);
            *(*(datasets+i)+j) = input;
        }
    }
    
    return datasets;
}

/*
 * Function: numInSet
 * ----------------------------
 * Gets the number of doubles in set
 *
 * i: index from getsets for loop
 * 
 * returns: number of doubles in set 
 */
int numInSet(int i){
    int set_num;
    printf("Enter the number of numbers in set %d then the contents of set separated by spaces: ", i+1);
    scanf("%d", &set_num);
    
    return set_num;
}

/*
 * Function: chooseSet
 * ----------------------------
 * Asks user for chosen data set
 *
 * datasets: the pointer to the pointer of doubles 
 * setsizes: the pointer to the sizes of each set
 * data_num: the number of data sets
 * 
 * returns: 0 on successful completion 
 */
int chooseSet(double **datasets, int *setsizes, int data_num){
    /*Initialize all variables used in function*/
    int input, setNum, size, i;
    double *set;
    
    printf("Enter the number of the data set on which you wish to do calculations :");
    scanf("%d", &input);
    printf("\n");
    setNum = input - 1;
    set = *(datasets + setNum);
    size = *(setsizes + setNum);
    i = prompt(set, size, datasets, setsizes, data_num);
    return 0;
}

/*
 * Function: prompt
 * ----------------------------
 * Prompts user to decided what calculation to complete on chosen data set
 *
 * set: the chosen set by the user
 * size: the size of the chosen set
 * datasets: the pointer to the pointer of doubles 
 * setsizes: the pointer to the sizes of each set
 * data_num: the number of data sets
 * 
 * returns: 0 on successful completion 
 */
int prompt (double *set, int size, double **datasets, int *setsizes, int data_num){
    /*Initialize all variables used in function*/
    int input, i=0;
    
    /*Repeatedly ask user for calculation options*/
    while(i == 0){
        printf("\n");
        printf("1. Find the minimum value.\n");
        printf("2. Find the maximum value.\n");
        printf("3. Calculate the sum of all the values.\n");
        printf("4. Calculate the average of all the values.\n");
        printf("5. Sort the value  in ascending order. (i.e. smallest to largest)\n");
        printf("6. Select a different data set.\n");
        printf("7. Exit the program.\n");
        printf("Choose one of the above options: ");
        scanf("%d", &input);
        printf("\n");
        switch (input){
            case 1:
                i = min(set, size);
                break;
            case 2:
                i = max(set, size);
                break;
            case 3:
                i = sum(set, size);
                break;
            case 4:
                i = average(set, size);
                break;
            case 5:
                i = sort(set, size);
                break;
            case 6:
                i = chooseSet(datasets, setsizes, data_num);
                break;
            case 7:
            default:
                quit(datasets, setsizes, data_num);
                break;
        }
        printf("\n");
    }
    /*Return 0 on successful completions*/
    return 0;
}

/*
 * Function: min
 * ----------------------------
 * Finds the minimum number in the chosen data set
 *
 * set: the chosen set by the user
 * size: the size of the chosen set
 * 
 * returns: 0 on successful completion 
 */
int min(double *set, int size){
    
    double min, temp;
    int i; 
    
    min = *(set+0);
    for(i=1; i<size; i++){
        temp = *(set+i);
        if(temp< min){
            min = temp;
        }
    }
    printf("The minimum value in the data set is: %lf", min);
    
    /*Return 0 on successful completions*/
    return 0;
}

/*
 * Function: max
 * ----------------------------
 * Finds the maximum number in the chosen data set
 *
 * set: the chosen set by the user
 * size: the size of the chosen set
 * 
 * returns: 0 on successful completion 
 */
int max(double *set, int size){
    
    double max, temp;
    int i; 
    
    max = *(set+0);
    for(i=1; i<size; i++){
        temp = *(set+i);
        if(temp > max){
            max = temp;
        }
    }
    printf("The maximum value in the data set is: %lf", max);
    
    /*Return 0 on successful completions*/
    return 0;
}

/*
 * Function: sum
 * ----------------------------
 * Finds the sum of the chosen data set
 *
 * set: the chosen set by the user
 * size: the size of the chosen set
 * 
 * returns: 0 on successful completion 
 */
int sum(double *set, int size){
    
    double sum, temp;
    int i; 
    
    sum = 0.0;
    for(i=0; i<size; i++){
        temp = *(set+i);
        sum+=temp;
    }
    printf("The sum of the data set is: %lf", sum);
    
    /*Return 0 on successful completions*/
    return 0;
}

/*
 * Function: average
 * ----------------------------
 * Finds the average of the chosen data set
 *
 * set: the chosen set by the user
 * size: the size of the chosen set
 * 
 * returns: 0 on successful completion 
 */
int average(double *set, int size){
    int i;
    double sum, avg, temp;
    
    sum = 0.0;
    for(i=0; i<size; i++){
        temp = *(set+i);
        sum+=temp;
    }
    avg = sum/size;
    
    printf("The average of the data set is: %lf", avg);
    
    /*Return 0 on successful completions*/
    return 0;
}

/*
 * Function: sort
 * ----------------------------
 * Outputs the sorted data set smallest to largest
 *
 * set: the chosen set by the user
 * size: the size of the chosen set
 * 
 * returns: 0 on successful completion 
 */
int sort(double *set, int size){
    
    double array[size], temp;
    int i,j; 
    
    for(i=0; i<size; i++){
        array[i] = *(set+i);
    }
    
    for (i = 1; i < size; i++) {
      for (j = 0; j < size - 1; j++) {
         if (array[j] > array[j + 1]) {
            temp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = temp;
         }
      }
    }
    
    printf("The sorted data set is: ");
    for (i = 0; i<size; i++){
        printf("%lf\t", array[i]);
    }
    
    /*Return 0 on successful completions*/
    return 0;
}

/*
 * Function: quit
 * ----------------------------
 * Frees the dynamically alloted arrays 
 * Quits the program
 *
 * datasets: the pointer to the pointer of doubles 
 * setsizes: the pointer to the sizes of each set
 * data_num: the number of data sets
 */
void quit(double **datasets, int *setsizes, int data_num){
    int i;
    for(i=0; i<data_num; i++){
        free(*(datasets+i));
    }
    free(datasets);
    free(setsizes);
    exit(1);
}