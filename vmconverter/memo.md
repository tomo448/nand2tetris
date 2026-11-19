|段階|作るもの|合否の判定|新しく学ぶこと|
|---|---|---|---|
|ステージ１|1行取り出し|"add"を入れると"add"と出力される|ストリームの使い方|
|1a|1行を、コマンドと引数に分ける|push constant 7 → push・constant・7。add → add だけ。 push that 5 → push・that・5||
|1b|最初の言葉から、種類を決める|push → C_PUSH、add → C_ARITHMETIC||
|ステージ2|push constant と add のアセンブリの型|SimpleAdd.tst を CPU エミュレータで動かして、.cmp と一致する|シンプルなスタックのアセンブリでの表現方法|
|ステージ3|引数なしコマンド|add,subなどを入れるとstackから値を取り出して，計算したものをスタックの一番上に入れる|constantセグメントに対応|
|ステージ4|論理演算|eq,gt ltを入れて正しいbool値が返ってくる|比較のアセンブリの書き方|
|ステージ5|算術・論理のテスト|StackTestを CPU エミュレータで動かして、.cmp と一致する|まとめてテストする方法|
|ステージ6|RAMの割り当て|BasicTestを CPU エミュレータで動かして、.cmp と一致する|変位の計算|
|ステージ7|RAMの割り当て|PointerTestを CPU エミュレータで動かして、.cmp と一致する|メモリマッピングのコード化|
|ステージ8|static割り当て|StaticTest.tst を CPU エミュレータで動かして、.cmp と一致する|staticセグメントと他の違い
