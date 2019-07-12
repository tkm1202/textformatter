テキストフォーマッタ
2018/7/26

[コンパイル方法]
% make

[実行方法]
% ./textformatter [filename]

[ソースコードファイルとモジュールの対応関係]
  mainmodule.c  メインモジュール
  lex.c          LEXモジュール
  header.c      ヘッダモジュール
  tab.c         タブモジュール
  strmanage.c   文字数管理モジュール
  linemanage.c  行・ページ管理モジュール
  ps.c           PS出力モジュール
