|名前|入力|出力|テストを行うファイル|
|---|---|---|---|
|name|enumクラスのCommandType 例:C_PUSHなど|CommandTypeの名前文字列　例:"C_PUSH"||
|GetCommandType|VMコマンド　例：push constant 2など|enumクラスのCommandType 例：C_PUSH||
|SplitString|VMコマンド(間に空白が何個あっても良い)　例：push constant 2など|vector<string> 例:{"push","constant","2"}|test_SplitString|
