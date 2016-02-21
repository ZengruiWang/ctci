#include<iostream>
using namespace std;

void printScreen(vector<char> screen, int w, int h){
	for(int i = 0; i < screen.size(); ++i){
		if(i % (w / 8) == 0) cout<<endl;
		for(int j = 7; j >= 0; --j){
			cout<<(screen[i]>>j & 1)<<" ";
		}
	}
	cout<<endl;
}
void drawHorizontal(vector<char> &screen, int w, int h, int x1, int x2, int y){
	int j = y * w / 8;
	int start = x1 / 8, end = x2 / 8;
	int start_offset = x1 % 8, end_offset = x2 % 8;
	if(start == end){ 
		screen[start + j] |= ((0xFF >> start_offset) & (0xFF << (7 - end_offset)));
		return;
	}
	for(int i = start; i <= end; ++i){
		char cur = screen[i + j];
		if(i == start)
			cur |= ((0xFF) >> start_offset);
		else if(i == end)
			cur |= ((0xFF) << (7 - end_offset));
		else cur |= (0xFF);
		screen[i + j] = cur;
	}
	
}


int main(){
	vector<char> screen(32, 0);
	int w = 32, h = 8;
	drawHorizontal(screen, w, h, 3, 4, 3);
	printScreen(screen, w, h);
	return 0;
}
