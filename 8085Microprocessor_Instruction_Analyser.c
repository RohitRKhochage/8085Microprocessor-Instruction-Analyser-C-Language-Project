	#include<stdio.h>
	#include<string.h>
	
	struct data
	{
		char mnemonic[10];
		char operand[2][10];
		char opcode[5];
		int byte;
	}info;
	FILE *fp;
	
	int main()
	{
		char getinst[25];
		char s[3][10],stype[2][25],sopcode[5];
		int i,j,c,c1,c2,wrong=0,right[3],hexall,sbyte;
		
		fp=fopen("8085InstructionData.dat","rb");
		
		again:
		for(i=0;i<3;i++) { right[i]=0; }
		printf("\033c\n\n\n");
		if(wrong==1)
		{
		printf("\n      ( Your entered previous instruction is invalid, please enter again.... )\n");
		wrong=0;
		}
		printf("\n   ------------------------------------------------------------------------------");
		printf("\n                               Fill required data");
		printf("\n   ------------------------------------------------------------------------------");
		printf("\n\n");
		printf("\n      ||>>> Enter the 8085 instruction");
		printf("\n                                   .......    ");
		scanf("\n");
		fgets(getinst,25,stdin);
		c=0;
		while(getinst[c]!='\n'&&getinst!='\0') { c++; }
		if(getinst[c-1]==';')
		{
			getinst[c-1]='\0'; 
		}
		else
		{
			getinst[c]='\0';
		}

		c=0;
		for(i=0;i<3;i++)
		{
			c1=0;
			while(getinst[c]!=' '&&getinst[c]!=','&&getinst[c]!='\0')
			{
				s[i][c1]=getinst[c];
				c++;
				c1++;
			}
			if(getinst[c]==' '||getinst[c]==','||getinst[c]=='\0') { s[i][c1]='\0'; }
			c2=0;
			while(s[i][c2]!='\n'&&s[i][c2]!='\0') { c2++; }
			s[i][c2]='\0';
			if(getinst[c]=='\0'&&i==0)
			{
				s[1][0]='\0';
				s[2][0]='\0';
				break;
			}
			if(getinst[c]=='\0'&&i==1)
			{
				s[2][0]='\0';
				break;
			}
			c++;
		}
		
		
		rewind(fp);
		while(fread(&info,sizeof(info),1,fp)==1)
		{
			if(strcmp(info.mnemonic,s[0])==0)
			{
			right[0]=1;
			i=0;
			second_check:
				if(strcmp(info.operand[i],s[i+1])==0)
				{
				right[i+1]=1;
					if(strcmp(info.operand[i],"A")==0||strcmp(info.operand[i],"B")==0||strcmp(info.operand[i],"C")==0||strcmp(info.operand[i],"D")==0||strcmp(info.operand[i],"E")==0||strcmp(info.operand[i],"H")==0||strcmp(info.operand[i],"L")==0)
					{ 
						strcpy(stype[i],"Register");
					}
					if(strcmp(info.operand[i],"M")==0)
					{ 
						strcpy(stype[i],"Memory location");
					}
					if(strcmp(info.operand[i],"SP")==0)
					{ 
						strcpy(stype[i],"Stack pointer");
					}
					if(strcmp(info.operand[i],"PSW")==0)
					{ 
						strcpy(stype[i],"Program status word");
					}
					if(strcmp(info.operand[i],"0")==0||strcmp(info.operand[i],"1")==0||strcmp(info.operand[i],"2")==0||strcmp(info.operand[i],"3")==0||strcmp(info.operand[i],"4")==0||strcmp(info.operand[i],"5")==0||strcmp(info.operand[i],"6")==0||strcmp(info.operand[i],"7")==0)
					{ 
						strcpy(stype[i],"Interrupt");
					}
				}
				
				c=0;
				while(s[i+1][c]!='\0') { c++; }
				hexall=0;
				for(j=0;j<c-1;j++)
				{
					if(s[i+1][j]=='0'||s[i+1][j]=='1'||s[i+1][j]=='2'||s[i+1][j]=='3'||s[i+1][j]=='4'||s[i+1][j]=='5'||s[i+1][j]=='6'||s[i+1][j]=='7'||s[i+1][j]=='8'||s[i+1][j]=='9'||s[i+1][j]=='A'||s[i+1][j]=='B'||s[i+1][j]=='C'||s[i+1][j]=='D'||s[i+1][j]=='E'||s[i+1][j]=='F')
					{
						hexall++;
					}
				}
				if(hexall==c-1)
				{
					if(strcmp(info.operand[i],"@")==0&&s[i+1][c-1]=='H'&&c==5)
					{
						right[i+1]=1;
						strcpy(stype[i],"16-bit address");
					}
				
					if(strcmp(info.operand[i],"#")==0&&s[i+1][c-1]=='H'&&c==3)
					{
						right[i+1]=1;
						strcpy(stype[i],"8-bit data");
					}
				
					if(strcmp(info.operand[i],"&")==0&&s[i+1][c-1]=='H'&&c==3)
					{
						right[i+1]=1;
						strcpy(stype[i],"8-bit port address");
					}
				}
				
				if(strcmp(info.operand[i],"$")==0)
				{
						right[i+1]=1;
						strcpy(stype[i],"Label");
				}
			
			if(right[0]==1&&right[1]==1&&i==0)
			{
				i=1;
				goto second_check;
			}
			
			}
			if(right[0]==1&&right[1]==1&&right[2]==1)
			{
				strcpy(sopcode,info.opcode);
				sbyte=info.byte;
				break;
			}
		}
		
		if(right[0]==1&&right[1]==1&&right[2]==1)
		{
			printf("\n   ------------------------------------------------------------------------------");
			printf("\n\n   ------------------------------------------------------------------------------");
			printf("\n      ||>>> Mnemonic          ....      %s",s[0]);
			if(s[1][0]!='\0')
			{
			printf("\n   ------------------------------------------------------------------------------");
			printf("\n      ||>>> Operand           ....      %s ( %s ) ",s[1],stype[0]);
			if(s[2][0]!='\0')
			{
			printf(",\n                                        %s ( %s )",s[2],stype[1]);
			}
			}
			printf("\n   ------------------------------------------------------------------------------");
			printf("\n      ||>>> Opecode           ....      %s",sopcode);
			printf("\n   ------------------------------------------------------------------------------");
			printf("\n      ||>>> Number of bytes   ....      %d",sbyte);
			printf("\n   ------------------------------------------------------------------------------");
			
			printf("\n\n     Use again ( 1 )...                                           Exit ( 0 )...  ");
			printf("\n                                     .... ");
			scanf("%d",&c);
			if(c==1) { goto again; }
			if(c==0) { return 0; }
		}
		else
		{
			wrong=1;
			goto again;
		}
		
		
	printf("\n\n...");
	return 0;
	}
