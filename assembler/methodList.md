| 名前             | 受け取る形                        | 返すもの                                                              | テストファイル                 | 覚えていたか          |
| -------------- | ---------------------------- | ----------------------------------------------------------------- | ----------------------- | --------------- |
| splitDJC       | D=D+1;JMP                    | dest,comp,jumpを持った構造体                                             | test_SplitDJC.cpp       | △受け取る形を変えた      |
| JudgeAC        | D;JMP                        | C_COMMAND                                                         | test_JudgeAC.cpp        | △受け取る形を変えた      |
| ConvertC       | D-A                          | 0010011                                                           | test_ConvertC.cpp       | △受け取る形と返すものを変えた |
| ConvertA       | A命令形式の文字列                    | バイナリ形式の文字列                                                        | test_ConvertA.cpp       | ×この名前の関数はない     |
| MapVar         | @i                           | addressMapに`i → 16` を入れる                                          | test_MapVar.cpp         | △受け取る形と返すものを変えた |
| MapLabel       | (LOOP)                       | addressMapに`LOOP → 1` を入れる                                        | test_MapLabel.cpp       | △受け取る形と返すものを変えた |
| FirstScan      | "D=1","(LOOP)","@14","@LOOP" | (LOOP)を見つけたら，MapLabelを呼び出す                                        | test_FirstScan.cpp      | △受け取る形と返すものを変えた |
| SecondScan     | "D=1","(LOOP)","@14","@LOOP" | "1110 1111 1101 0000","0000 0000 0000 1110","0000 0000 0000 0011" | test_SecondScan.cpp     | △受け取る形と返すものを変えた |
| ConvertVar     | @i                           | 16                                                                | test_MapVar.cpp         | △受け取る形と返すものを変えた |
| PutInContainer | ファイルストリーム                    | "D=1","(LOOP)","@14","@LOOP"                                      | test_PutInContainer.cpp | △受け取る形と返すものを変えた |
| ConvertD       | ADM                          | 111                                                               | test_ConvertD.cpp       | ×               |
| ConvertJ       | JGT                          | 001                                                               | test_ConvertJ.cpp       | ×               |
| ParserA        | @1                           | 0000 0000 0000 0001                                               | test_ParserA.cpp        | ×               |
| ParserC        | D=D+1;JMP                    | 1110 0111 1101 0111                                               | test_ParserC.cpp        | ×               |
| is_number      | 17                           | true                                                              | なし                      | ×               |

