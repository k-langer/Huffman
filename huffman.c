#include <huffman.h>

void add_sample(Sample_t ** PDF, unsigned char sample) {
    Sample_t * head = *PDF; 
    Sample_t * tail; 
    char first = 0; 
    if (!head) {
        first = 1; 
    }
    while (head != NULL && head->value != sample) {
        tail = head; 
        head = head->next; 
    }
    if (head == NULL) {
        head = calloc(sizeof(Sample_t),1);
        if (tail) {
            tail->next = head;
        }
        head->frequency = 1; 
        head->cdf = 1; 
        head->value = sample; 
        head->next = NULL; 
    } else {
        head->frequency += 1; 
        head->cdf += 1; 
    }
    if (first) {
        *PDF = head; 
    }
}
void print_list(Sample_t * list, int len) {
    Sample_t * head = list; 
    Sample_t * sym_count;
    int length;
    double avg_length = 0;  
    while (head != NULL) {
        if (head->value) {
            sym_count = head->uplink;
            length = 0;
            while  (sym_count) {
                length++;
                sym_count= sym_count->uplink; 
            }
            printf("%d %d %d\n",head->value, head->frequency, length);
            avg_length += length*(head->frequency/(len+0.0)); 
        }
        head = head->next;  
   }
   printf("Avg %f\n",avg_length);
} 
Sample_t * uplink(Sample_t ** PDF, int cdf) {
    Sample_t * head = *PDF; 
    Sample_t * last; 
    while (head != NULL) {
        last = head; 
        head = head->next;  
    }
    head = calloc(1, sizeof(Sample_t)); 
    last->next = head; 
    head->cdf = cdf; 
    return head;
} 
void * assignSymbols(Sample_t * PDF, int sample_count)  {
    while (PDF && PDF->cdf != sample_count) {
        int freq1 =sample_count, freq2 = sample_count; 
        Sample_t * head = PDF; 
        Sample_t * min1 = NULL, * min2 = NULL; 
        while (head) {
            if (!head->uplink) {
                if (head->cdf < freq1) {
                    if (freq1 < freq2) {
                        freq2 = freq1;        
                        min2 = min1; 
                    }
                    freq1 = head->cdf; 
                    min1 = head; 
                } 
                if (head->cdf < freq2 && min1 != head) {
                    freq2 = head->cdf;
                    min2 = head; 
                }
            }
            head = head->next; 
        }
        
        Sample_t * link = uplink(&PDF, freq1+freq2);
        min1->uplink = link;
        min2->uplink = link; 
        min1->codeword = 0; 
        min2->codeword = 1;
        if (freq1+freq2 >= sample_count) {
            break;
        } 
        //printf("min %d %d min %d %d\n",min1->value,freq1,min2->value,freq2);
        
    }
}

int main(int argc, char *argv[]) {
    char * filename; 
    Sample_t * PDF = NULL; 
    if (argc < 2) {
        return -1; 
    }
    filename = argv[1]; 
    FILE *f; 
    f = fopen(filename,"r");
    if (f == NULL) {
        return -1;
    }
    unsigned char byte; 
    unsigned int sample_count = 0; 
    while (fscanf(f,"%c",&byte) != EOF) {
        add_sample(&PDF,byte); 
        sample_count++; 
    }
    assignSymbols(PDF, sample_count);
    print_list(PDF,sample_count);
    printf("%d\n",sample_count);
    //printf("%s\n",filename);
    fclose(f); 
  //fixed a = 1.1;
   return 0;
}
