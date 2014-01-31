程序运行方法
windows : segmenter.exe < input.txt > output.txt   必须是gb18030编码
Linux : ./segmenter < input.txt > output.txt   必须是utf8编码

bin
bin/Linux                           Linux可执行文件
bin/Linux/build_dict                从分好的文件建立字典的程序
bin/Linux/segmentor                 分词程序
bin/Linux/normalize_table.dat       正则化表(utf8)
bin/Linux/dict.dat                  字典(utf8)
bin/win32                           Win32可执行文件
bin/win32/build_dict.exe            从分好的文件建立字典的程序
bin/win32/segmentor.exe             分词程序
bin/win32/normalize_table.dat       正则化表(gb18030)
bin/win32/dict.dat                  字典(gb18030)

doc
doc/class diagram.png               类图png格式
doc/class diagram.uxf               umlet类图文件
doc/flow chart.odg                  流程图 openoffice draw文件
doc/中文分词程序文档.pdf           程序文档pdf格式
doc/中文分词程序文档.odt           程序文档 openoffice格式

src                                 源代码
src/segmentor.cpp                   分词程序源代码
src/build_dict.cpp                  词典建立程序源代码

test                                测试结果
test/msr_score.txt                  msr测试集测试结果
test/pku_score.txt                  pku测试集测试结果
