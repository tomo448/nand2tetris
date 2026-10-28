// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
@i
M=0 //M[i]=0
@SCREEN //A=SCREEN
D=A //D=SCREEN
@adrr //A=adrr
M=D //M[adrr]=SCREEN
@LOOP
0;JMP //LOOPにジャンプ
(LOOP)
@i //A=i M[i]=ループ回数
D=M //D=ループ回数
@32
D=A-D //D=32-i
@END
D;JLE //D<=0ならば(END)にジャンプ
@adrr
A=M //A=M[adrr]
M=-1 //M[M[adrr]]=-1　塗る
D=A //D=M[adrr]
@adrr //A=adrr
M=D+1 //M[adrr]=16384+1 //進める
@i
M=M+1 //ループ回数を増やす　A=i
@LOOP
0;JMP //LOOPの先頭に戻る
(END)
@END
0;JMP
