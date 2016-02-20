#include<iostream>
#include<climits>
#include<cmath>
using namespace std;

void printBinary(int n){
    int arr[32];
    int len = 8*sizeof(n);
    int mask = 1;
    int index = 0;
    while(len--){
        if(n&mask)
            arr[index] = 1;
        else
            arr[index] = 0;
        index++;
        mask <<= 1;
    }
    for(int i=31; i>=0; i--){
        cout<<arr[i];
    }
    cout<<'\n';
}
int getNextLargest(int n){
	int c1 = 0, i;
	//find the right-most non-trailing 0
	for(i = 0; i < 32; ++i){
		if((n & (1 << i)) == 0 && c1 > 0){
			//set the ith bit to 1
			n |= (1 << i);
			break;
		}else if((n & (1 << i)) != 0){
			c1++;
		}
	}
	if(i == 32) return -1;
	//clear lower [0, i - 1] bit
	int allOnes = ~0;
	n &= (allOnes << i);
	//get the mask which has c1 - 1 1's in the lower [0, c1 - 2]
	int mask = (1 << (c1 - 1)) - 1;
	return mask | n;
}
int getNextSmallest(int n){
	int c0 = 0, i;
	for(i = 0; i < 32; ++i){
		if((n & (1 << i)) != 0 && c0 > 0){
			//clear the ith bit 
			n &= ~(1 << i);
			printBinary(n);
			break;
		}else if((n & (1 << i))  == 0){
			c0++;
		}
	}
	if(i == 32) return -1;
	//set lower [0, i - 1] to 1's
	n |= (1 << i) - 1;
	printBinary(n);
	//clear lower c0 - 1 bits
	n &= (~0)<<(c0 - 1);
	printBinary(n);
	return n;
}
int main(){
	int n = 13948;
	printBinary(n);
	int res = getNextSmallest(n);
	cout<<"result:"<<endl;
	printBinary(res);
	cout<<res<<endl;
}
}


