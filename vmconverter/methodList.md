|名前|入力|出力|テストを行うファイル|
|---|---|---|---|
|GetCommandType|VMコマンド　例：push constant 2など|enumクラスのCommandType 例：C_PUSHなど，空の文字列や間違ったコマンドを入力すると例外を投げる|test_GetCommandType|
|GetCommandType2|VMコマンド　例：push constant 2など,こちらは空白で区切られた配列を入力で受け取る|enumクラスのCommandType 例：C_PUSHなど，空の文字列や間違ったコマンドを入力すると例外を投げる|test_GetCommandType|
|SplitString|VMコマンド(間に空白が何個あっても良い)　例：push constant 2など|vector<string> 例:{"push","constant","2"}|test_SplitString|
|GetArgument1|SplitString で分けたあとのvector<string> 例:{"push","constant","2"},{"add"}|"constant","add"(コマンドによって返す引数が違うことに注意)|test_GetArgument|
|GetArgument2|SplitString で分けたあとのvector<string> 例:{"push","constant","2"},push,popの時だけ呼ぶ|2|test_GetArgument|
|CheckRightStyle|分割後の命令，正しい命令形式がくるとは限らない|正しくない命令形式であれば例外を投げる．正しければ何もしない|test_CheckRightStyle|
|PutInContainer|入力ファイルストリーム|空行とコメントを取り除いた命令群．命令の1行は一つの文字列になっている.末尾に空白があればそれは取り除かれる．　例{"push constant 7","push constant 5","add"}|test_PutInContainer|
|Parser.hasMoreCommands|なし|次のコマンドがあるかどうかをbool値で返す|test_ParserClass|
|Parser.advance|なし|次のコマンドがあるかをチェック(hasMoreCommands())し，あれば_lineを次に進める．なければ例外を返す|test_ParserClass|
|Parser.commandType|なし|例:C_PUSH,C_POPなど|test_ParserClass|
|Parser.arg1|なし|例:local,constatnt,addなど|test_ParserClass|
|Parser.arg2|なし|pushとpopの時のみ呼び出す．int型を返す　例 2,3など|test_ParserClass|
|CodeWriter.writeArithmetic|vm命令コマンド．通常はパサーからarg1を受け取る．C_ARITHMETICの場合しか呼び出さない|手作業で作成したasmコマンド列を返す．|test_CodeWriter|
|CodeWriter.writePushPop|vm命令コマンド．通常はパサーからCommandType，arg1，arg2を受け取る．C_PUSU,C_POPの場合しか呼び出さない|手作業で作成したasmコマンド列を返す|test_CodeWriter|
|CodeWriter.writeAdd|なし|add.asmに書いたコマンドをそのまま返す．writeArithmeticから呼ばれるヘルパー関数|test_CodeWriter|
|CodeWriter.setFileName|現在操作しているファイル名|なし||
