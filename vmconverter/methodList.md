|名前|入力|出力|テストを行うファイル|
|---|---|---|---|
|GetCommandType|VMコマンド　例：push constant 2など|enumクラスのCommandType 例：C_PUSHなど，空の文字列や間違ったコマンドを入力すると例外を投げる|test_GetCommandType|
|SplitString|VMコマンド(間に空白が何個あっても良い)　例：push constant 2など|vector<string> 例:{"push","constant","2"}|test_SplitString|
|GetArgument1|SplitString で分けたあとのvector<string> 例:{"push","constant","2"},{"add"}|"constant","add"(コマンドによって返す引数が違うことに注意)|test_GetArgument|
|GetArgument2|SplitString で分けたあとのvector<string> 例:{"push","constant","2"},push,popの時だけ呼ぶ|2|test_GetArgument|
|Parser.hasMoreCommands()|なし|次のコマンドがあるかどうかをbool値で返す|test_ParserClass|
|Parser.advance()|なし|次のコマンドがあるかをチェック(hasMoreCommands())し，あれば_lineを次に進める．なければ例外を返す|test_ParserClass|
|Parser.commandType()|なし|例:C_PUSH,C_POPなど|test_ParserClass|
|Parser.arg1()|なし|例:local,constatnt,addなど|test_ParserClass|
|Parser.arg2()|なし|pushとpopの時のみ呼び出す．int型を返す　例 2,3など|test_ParserClass|
