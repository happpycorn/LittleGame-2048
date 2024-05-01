#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define N 4//方陣邊長 
#define WIN 2048//遊戲獲勝目標

void output(int (*a)[N]){//輸出4*4表格， 
	int i,j;
		printf("\n");
		printf("┏━━━━┳━━━━┳━━━━┳━━━━┓");//頂邊框 
		printf("\n");
	for(i=0;i<N;i++){printf("┃") ;
		for(j=0;j<N;j++){
			if(a[i][j]==0) printf("    ┃");//如果數值為零則輸出空白 
			else  printf("%4d┃",a[i][j]);
		}
		if(i!=3)
		printf("\n┣━━━━╋━━━━╋━━━━╋━━━━┫\n");//層邊框 
		else 	printf("\n┗━━━━┻━━━━┻━━━━┻━━━━┛\n");//底邊框 
	}
}  
int sj24(){//獲取隨機數2或4 
	int s[8]={2,2,2,2,2,2,2,4},i,j;//以概率7:1建立2和4的隨機數種子 
	srand((unsigned)time(NULL));
	i=(rand())%8;//以時間為種子得到0~7的隨機數 
	return s[i];
}
int input(){//輸入上下左右指令控制遊戲 
	int m;
	if(getch()==0xE0){ //對鍵入的命令進行識別 
		switch(getch()){//十位1表示水平移動2表示豎直移動，各位1表示向小座標移動2表示向大座標移動 
			case 72: return 21;break;//輸入上 
			case 80: return 22;break;//輸入下 
			case 75: return 11;break;//輸入右 
			case 77: return 12;break;//輸入左
			default:{//若命令不符合要求，運用遞迴重新得到命令 
				printf("請輸入正確的指令！(～￣(OO)￣)ブ\n");
				return input();	
			}
	}
}
	else {//若命令不符合要求，運用遞迴重新得到命令 
		printf("請輸入正確的指令！(～￣(OO)￣)ブ\n\n");
		return input();
		}
}
void move(int (*a)[N]){ //通過呼叫input函式得到正確的命令，根據命令移動資料 
	int x,i,j,k,s[N][N],t=0;
 	x=input();
 	for(i=0;i<N;i++){
		for(j=0;j<N;j++) s[i][j]=a[i][j];//拷貝移動前方陣方便以後檢查 
	}
 	if(x/10==1){//水平移動 
 		if(x%10==1){//向小座標移動 
		 	for(i=0;i<N;i++)
			{
				for(k=0;k<3;k++)
				{
					//  核心演算法介紹 
		 			for(j=N-1;j>0;j--)
					{           //第一步，先將一排資料重後往前一個個向前推（除去前面和中間的0） 
						if(a[i][j-1]==0) {        //為確保移動完全經推理最多3次完成所有移動所有執行3次該演算法 
						a[i][j-1]=a[i][j];        //第二步，將相鄰兩兩相同的數相加賦值前者後者賦0 
						a[i][j]=0;                // 第三部，重複第一步操作去除新產生的0，總操作完成 
 					}                         //PS:所有方向演算法原理相同 
 	     		}
 	     		}
		 		for(j=0;j<N-1;j++){
 					if(a[i][j]==a[i][j+1]) {
						a[i][j]=a[i][j]+a[i][j+1];
						a[i][j+1]=0;
					}
				}
		 		for(k=0;k<3;k++){
		 		for(j=N-1;j>0;j--){
 					if(a[i][j-1]==0) {
					a[i][j-1]=a[i][j];
 					a[i][j]=0;
 					}
 	     		}
 	     		}
		 	}	 
		 }
		 else{//向大座標移動 
		 	for(i=0;i<N;i++){for(k=0;k<3;k++){
		 		for(j=0;j<N-1;j++){
 					if(a[i][j+1]==0) {
					a[i][j+1]=a[i][j];
 					a[i][j]=0;
 					}
 	     		}
 	     		}
				for(j=N-1;j>0;j--){
 					if(a[i][j]==a[i][j-1]) {
						a[i][j]=a[i][j]+a[i][j-1];
						a[i][j-1]=0;
					}
				}
		 		for(k=0;k<3;k++){
		 		for(j=0;j<N-1;j++){
 					if(a[i][j+1]==0) {
					a[i][j+1]=a[i][j];
 					a[i][j]=0;
 					}
 	     		}
 	     		}
		 	}	 
		 }
	 }
 	else{//豎直移動 
 		if(x%10==1){//向小座標移動 
		 for(i=0;i<N;i++){for(k=0;k<3;k++){
				for(j=N-1;j>0;j--){
 					if(a[j-1][i]==0) {
					a[j-1][i]=a[j][i];
 					a[j][i]=0;
 					}
 	     		}
 	     		}
				for(j=0;j<N-1;j++){
 					if(a[j][i]==a[j+1][i]) {
						a[j][i]=a[j][i]+a[j+1][i];
						a[j+1][i]=0;
					}
				}
		 		for(k=0;k<3;k++){
				for(j=N-1;j>0;j--){
 					if(a[j-1][i]==0) {
					a[j-1][i]=a[j][i];
 					a[j][i]=0;
 					}
 	     		}
 	     		}	
			}
		 }
		 else{//向大座標移動 
		 	for(i=0;i<N;i++){for(k=0;k<3;k++){
		 		for(j=0;j<N-1;j++){
 					if(a[j+1][i]==0) {
					a[j+1][i]=a[j][i];
 					a[j][i]=0;
 					}
 	     		}
 	     		}
				for(j=N-1;j>0;j--){
 					if(a[j][i]==a[j-1][i]) {
						a[j][i]=a[j][i]+a[j-1][i];
						a[j-1][i]=0;
					}
				}
		 		for(k=0;k<3;k++){
		 		for(j=0;j<N-1;j++){
 					if(a[j+1][i]==0) {
					a[j+1][i]=a[j][i];
 					a[j][i]=0;
 					}
 	     		}
 	     		}
		 	}
		 }
	 }
	 for(i=0;i<N;i++){//檢查是否為有效移動 
		for(j=0;j<N;j++) {
			if (s[i][j]!=a[i][j]) t=1;
		}
		}
		if(t){
			begin(a);	
			Sleep(60);//為讓玩家知道移動後隨機數出現位置，讓其延遲出現 
			get(a);	
			begin(a);
		}  
		else printf("選擇其他方向試試(￢_￢)"); 
}
void get(int (*a)[N]){//在4*4表格中空板位置隨機獲得數字 
	int i,j;
	srand((unsigned)time(NULL));
	do{
			i=(rand())%4;
			j=(rand())%4;	
	} while(a[i][j]!=0); 
	 a[i][j]=sj24();
}  
void begin(int (*a)[N]){//清屏並列印開頭 
	system("cls"); 
	printf("        小遊戲2048\n\n  ");
	printf("   鍵入上下左右控制\n");
	output(a);
} 
int test(int (*a)[N]){//判斷是否遊戲完成 
	int i,j,k=0,m=0,n=0;
		printf("\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(a[i][j]==0)m=1;//檢查方陣中是否有0 
			if(a[i][j]==WIN)k=1; //檢查方陣中是否有目標數字 
		}
	}
	if (k){//如果發現目標數字判定遊戲獲勝 
		printf("YOU WIN! \(^o^)/YES!"); 
		return 0;
	}
	else{
		if(!m){//如果方陣中無0且無相鄰數字相等則判定遊戲失敗，反之遊戲繼續 
		 	for(i=0;i<N;i++){
				for(j=0;j<N-1;j++)
					if(a[i][j]==a[i][j+1]||a[j][i]==a[j+1][i]) n=1;
			}
	   	if(n) return 1;
		else{
			printf("GAME OVER!〒▽〒");
			return 0;
			}
		}
		else return 1;   
	}		 
}
void main(){
	 int a[N][N]={0};
	 get(a);get(a);begin(a);//起始時方陣有兩個隨機數 
	while(test(a)) move(a); //只有通過tset函式檢查才能繼續遊戲 
} //謝謝 