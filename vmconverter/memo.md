|段階|作るもの|合否の判定|新しく学ぶこと|
|---|---|---|---|
|ステージ１|Parserクラス|vectorを受け取って，クラスに格納する．|ストリームの使い方|
|1a|1行を、コマンドと引数に分ける|push constant 7 → push・constant・7。add → add だけ。 push that 5 → push・that・5.methodList.md に1行|文字列の分割の方法|
|1b|最初の言葉から、種類を決める|push → C_PUSH、add → C_ARITHMETIC,methodList.md に1行|mapコンテナを使って，コマンドとその種類をマッチングする方法|
|1c|引数を返す|push constant 7 →arg1 constant arg2 7 ,add→arg1 add arg2 例外を出す.methodList.md に1行.|クラスメソッドのarg1,arg2,コンストラクタ，constant の範囲（0〜32767）を確かめるか、あとで決める|
|1c'|正しい命令形式を受け取る1行読み取り関数|push constant → 例外、add 3 → 例外、push constant x → 例外、正しい行 → 何も起きない，pop constant は例外にする|正しい命令形式以外の時の例外スロー|
|1d|Parserのクラス|{"push constant 3","add"}→C_PUSH,constant,3/C_ARITHMETIC,add/コマンドがない.methodList.md に1行||
|ステージ2|push constant と add のアセンブリの型|SimpleAdd.tst を CPU エミュレータで動かして、.cmp と一致する|シンプルなスタックのアセンブリでの表現方法|
|ステージ3|引数なしコマンド|add,subなどを入れるとstackから値を取り出して，計算したものをスタックの一番上に入れる|constantセグメントに対応|
|ステージ4|論理演算|eq,gt ltを入れて正しいbool値が返ってくる|比較のアセンブリの書き方|
|ステージ5|算術・論理のテスト|StackTestを CPU エミュレータで動かして、.cmp と一致する|まとめてテストする方法|
|ステージ6|RAMの割り当て|BasicTestを CPU エミュレータで動かして、.cmp と一致する|変位の計算|
|ステージ7|RAMの割り当て|PointerTestを CPU エミュレータで動かして、.cmp と一致する|メモリマッピングのコード化|
|ステージ8|static割り当て|StaticTest.tst を CPU エミュレータで動かして、.cmp と一致する|staticセグメントと他の違い


Parserモジュール
|メソッドの名前|入力|戻り値|動作|
|---|---|---|---|
|コンストラクタ|vector<string>|なし|コマンドを1行ずつ取り出したコンテナをメンバー変数に入れる|
|hasMoreCommands|なし|bool値|次の行にコマンドがあるかをチェックする(vectorに1行ずつ入れて，最後の行かチェックする関数)|
|advance|なし|なし|hasMoreCommandsがtrueの場合のみ呼ばれる．現在読んでいるstringを次の行に変換する|
|CommandType|なし|enum class CommandType|その行の最初の文字列を確認し，それがどのVMコマンドを指しているかを返す|
|arg1|なし|string|push,pop命令の場合には利用するセグメント，算術論理命令の場合はそのコマンドを返す|
|arg2|なし|int|現コマンドの第二引数を返す|


11/23 記録　VME は自分のコードを試していない。RAM[0] が 258。次はラベルの数から
11/24 記録　アセンブリ言語でメソッドを書く際はラベルの使い回しに注意する．名前解決は自分の責任
２回呼び出すと違うラベルが作成されることを確認するテストとジャンプ命令が正しいかどうかのチェックを行うテストをしなければいけなかった．


nand2tetris 8章
|段階|作るもの|合否の判定|新しく学ぶこと|
|---|---|---|---|
|ステージ１|ラベルコマンド|label nullなどを入力して(null)が作成される．先頭が数字のラベルの場合は例外を出す|特になし|
|ステージ２|gotoコマンド| goto labelを入力して@label　0;JMPが出力される|特になし|
|ステージ３|if goto コマンド|if goto labelを入力して@label　0;JNEが出力される|特になし|
