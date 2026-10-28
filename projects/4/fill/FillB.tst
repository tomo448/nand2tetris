// 段階 B のテスト: 画面の1行目（RAM[16384]〜RAM[16415] の32語）がすべて黒（-1）になり、
// 2行目の最初の語（RAM[16416]）は白（0）のままかを確かめる。
// Fill.asm を直接読む（.hack は要らない）。

load Fill.asm,
output-file FillB.out,
compare-to FillB.cmp,
output-list RAM[16384]%D2.6.2 RAM[16400]%D2.6.2 RAM[16415]%D2.6.2 RAM[16416]%D2.6.2;

repeat 5000 {
  ticktock;
}
output;
