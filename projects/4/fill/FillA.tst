// 段階 A のテスト: 画面の最初の語（RAM[16384]）だけが黒（-1）になり、
// 次の語（RAM[16385]）は白（0）のままかを確かめる。
// Fill.asm を直接読む（.hack は要らない）。

load Fill.asm,
output-file FillA.out,
compare-to FillA.cmp,
output-list RAM[16384]%D2.6.2 RAM[16385]%D2.6.2;

repeat 100 {
  ticktock;
}
output;
