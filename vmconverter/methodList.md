|名前|入力|出力|テストを行うファイル|
|---|---|---|---|
|GetCommandType|VMコマンド　例：push constant 2など|enumクラスのCommandType 例：C_PUSHなど，空の文字列や間違ったコマンドを入力すると例外を投げる|test_GetCommandType|
|SplitString|VMコマンド(間に空白が何個あっても良い)　例：push constant 2など|vector<string> 例:{"push","constant","2"}|test_SplitString|
