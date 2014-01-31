char cmd;
do
{
	cin >> cmd;
	switch (cmd)
	{
		case '1':
			new_file();
			show_menu();
			break;
		case '2':
			open_file(); 
			show_menu();
			break;
		case '3':
			cout << "Exit Program." << endl;
			break;
		default:
			cout << "Error Command." << endl;
			cin.clear();
			cin.sync();
			break;
	}
}while (cmd != 3);

