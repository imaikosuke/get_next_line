# Get Next Line

42TokyoのCommon Coreの課題として取り組みました。

## 概要

" get_next_line() " 関数を繰り返し呼び出す（ループを使うなど）ことで、ファイル・ディスクリプタが指すテキスト・ファイルを1行ずつ読み込むことができる関数です。

また、他に読み込むものがない場合やmallocなどのエラーが発生した場合はNULLを返します。

ファイルを読み込むときも、標準入力から読み込むときも、関数は同様の挙動を行います。
