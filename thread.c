/*
Name:Sanskriti Agrawal
Roll No:1810110216 
Teammate Name:Bhavya Jain
Roll no:1810110054

*/
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

/* structure for passing data to threads */ 
 typedef struct {  
 int start;
 int end;  
 } parameters;
  
 int arr[10];
 int sorted[10];
 int arr1[5],arr2[5];
 
 
 
 
 void merge(int start, int mid , int end){
  int i, j, k; 
    int left_len = mid - start + 1; 
    int right_len =  end - mid; 
  
     
    int  LEFT[left_len], RIGHT[right_len];   // create temporary arrays 
  
    
    for (i = 0; i < left_len; i++) {
       LEFT[i] = arr[start + i]; 
       }
    for (j = 0; j < right_len; j++){ 
        RIGHT[j] = arr[mid + 1+ j]; 
        }
  
    //merging these temp arrays 
    i = 0;  
    j = 0;  
    k = start; 
    while (i < left_len && j < right_len) 
    { 
        if (LEFT[i] <= RIGHT[j]) 
        { 
            arr[k] =LEFT[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = RIGHT[j]; 
            j++; 
        } 
        k++; 
    } 
  
    //Copy the remaining elements of L[], if there are any 
    while (i < left_len) 
    { 
        arr[k] =LEFT[i]; 
        i++; 
        k++; 
    } 
  
    //Copy the remaining elements of R[], if there are any 
    while (j < right_len) 
    { 
        arr[k] = RIGHT[j]; 
        j++; 
        k++; 
    }  
} 
 
 
 
 //basic mergesort function
 void merge_sort(int start,int end){
 if(start<end){
 int mid=start+(end-start)/2;
 merge_sort(start,mid);
 merge_sort(mid+1,end);
 merge(start,mid,end);
 }
 }
 
 
 
 //thread invokes this function first
 void *thread_mergesort(void *args){
 parameters *params = (parameters *)args;
 int left = params->start;
 int right = params->end;
 if(left<right)
 {
 merge_sort(left,right);
 }
 }
 
 
 
 
 
 
 

 
 
 //the thread that merges the previous two threads 
 void *merge_thread(void *mer_args){
 parameters *param = (parameters *) mer_args;
    int begin = param->start,
        end = param->end,
        mid= 5;


    int i = 0, j = 0, k = 0; 
  
    // Traverse both array 
    while (i<5 && j <5) 
    { 
         
        if (arr1[i] < arr2[j]) 
            sorted[k++] = arr1[i++]; 
        else
            sorted[k++] = arr2[j++]; 
    } 
  
    // Store remaining elements of first array 
    while (i < 5) 
        sorted[k++] = arr1[i++]; 
  
    // Store remaining elements of second array 
    while (j < 5) 
        sorted[k++] = arr2[j++]; 
 
}

 
 
 
 
   
   
   
 void main(){
 srand(time(NULL));
 for(int i=0 ; i<10 ; i++)
 arr[i] = rand() % 100;
 
 printf("The unsorted array is:\n");
 for(int j=0;j<10;j++){
 
 printf("%d, ",arr[j]);
 }
 
 pthread_t threads[3];
 parameters *data1 = (parameters *) malloc(sizeof(parameters)); // set sorting parameters for the first sublist
 data1->start = 0;
 data1->end = 4; 
 pthread_create(&threads[0],NULL,thread_mergesort,data1); // sort the first subarray

 parameters *data2 = (parameters *) malloc(sizeof(parameters)); // set sorting parameters for the second subarray
 data2->start = 5;
 data2->end = 9;
 pthread_create(&threads[1],NULL,thread_mergesort,data2);  // sort the second subarray

 pthread_join(threads[0],NULL);  // waiting for first thread to terminate
for(int i=0;i<=4;i++){
 arr1[i]=arr[i];    // an array to store the first half of sorted elements
 }
 pthread_join(threads[1],NULL); // waiting for second thread to terminate
 for(int i=5;i<=9;i++){
 arr2[i-5]=arr[i];  // an array to store the second half of sorted elements 
 } parameters *mer_args = (parameters *) malloc(sizeof(parameters));
 mer_args->start = 0;
 mer_args->end = 10;
 pthread_create(&threads[2],NULL,merge_thread,&mer_args);
 pthread_join(threads[2],NULL);     // waiting for merging thread to terminate
 printf("\nThe sorted array is:\n");
 for(int i=0;i<10;i++){
 printf("%d, ",sorted[i]);
}
 }
 
 
 
  
 
 
 
 
 

 
 
 
 
 

 
 
 
 
 
 
 
