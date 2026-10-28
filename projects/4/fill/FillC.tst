// 段階 C のテスト: 画面全体（RAM[16384]〜RAM[24575] の8192語）がすべて黒（-1）になるかを確かめる。
// 最初・途中・最後の語を見る。最後の語（24575）が黒でなければ、1語足りない。
// Fill.asm を直接読む（.hack は要らない）。時間がかかるので No Animation で。

load Fill.asm,
output-file FillC.out,
compare-to FillC.cmp,
output-list RAM[16384]%D2.6.2 RAM[16415]%D2.6.2 RAM[20000]%D2.6.2 RAM[24574]%D2.6.2 RAM[24575]%D2.6.2;

repeat 300000 {
  ticktock;
}
output;
