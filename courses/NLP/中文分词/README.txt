�������з���
windows : segmenter.exe < input.txt > output.txt   ������gb18030����
Linux : ./segmenter < input.txt > output.txt   ������utf8����

bin
bin/Linux                           Linux��ִ���ļ�
bin/Linux/build_dict                �ӷֺõ��ļ������ֵ�ĳ���
bin/Linux/segmentor                 �ִʳ���
bin/Linux/normalize_table.dat       ���򻯱�(utf8)
bin/Linux/dict.dat                  �ֵ�(utf8)
bin/win32                           Win32��ִ���ļ�
bin/win32/build_dict.exe            �ӷֺõ��ļ������ֵ�ĳ���
bin/win32/segmentor.exe             �ִʳ���
bin/win32/normalize_table.dat       ���򻯱�(gb18030)
bin/win32/dict.dat                  �ֵ�(gb18030)

doc
doc/class diagram.png               ��ͼpng��ʽ
doc/class diagram.uxf               umlet��ͼ�ļ�
doc/flow chart.odg                  ����ͼ openoffice draw�ļ�
doc/���ķִʳ����ĵ�.pdf           �����ĵ�pdf��ʽ
doc/���ķִʳ����ĵ�.odt           �����ĵ� openoffice��ʽ

src                                 Դ����
src/segmentor.cpp                   �ִʳ���Դ����
src/build_dict.cpp                  �ʵ佨������Դ����

test                                ���Խ��
test/msr_score.txt                  msr���Լ����Խ��
test/pku_score.txt                  pku���Լ����Խ��
