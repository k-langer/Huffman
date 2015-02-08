#include <stdio.h>
#include <stdlib.h>

typedef struct Sample {
    unsigned char value; 
    unsigned int frequency; 
    struct Sample * next;
    unsigned int cdf; 
    unsigned int codeword; 
    unsigned int length;  
    struct Sample * uplink; 
} Sample_t; 

//Add a raw sample to the list to create PDF
void add_sample(Sample_t ** PDF, unsigned char sample);
//Print valid samples and average code word length
void print_list(Sample_t * list, int len);
//Link up samples on binary tree
Sample_t * uplink(Sample_t ** PDF, int cdf);
//Assign codewords to raw samples
void * assignSymbols(Sample_t * PDF, int sample_count);
