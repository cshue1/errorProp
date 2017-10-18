Error::Error()
{
    anchor = NULL;
    end    = NULL;
}

void Error::addEntry(string n, double v, bool c)
{
    char s;
    dataType *addData;
    addData = new dataType;
    addData->name = n;
    addData->value = v;
    if (!c)
    {
	cout << "Which error would you like to enter?" << endl;
	do
	{
	    cout << "(R = relative, A = absolute)" << endl;
	    cin  >> s;
	}while (s != 'R' && s != 'r' && s != 'A' && s != 'a');
	cout << "Enter the value of the error: ";
	if (s == 'R' || s == 'r')
	{
	    cin >> addData->relERR;
	    addData->absERR = calcAbsERR(addData->value,addData->relERR);
	}
	else if (s == 'A' || s == 'a')
	{
	    cin >> addData->absERR;
	    addData->relERR = calcRelERR(addData->value,addData->absERR);
	}
	addData->rules = false;
    }
    else
    {
	propRules(addData);
    }

    addData->link = NULL;
    
    if (anchor == NULL)
    {
	anchor = addData;
    }
    else
    {
	end->link = addData;
    }
    end = addData;
    cout << addData->name << " was added." << endl << endl;
    
}

void Error::propRules(dataType* add)
{
    int select, constant;
    double value;
    string var;
    float n1,n2;
    dataType *find;
    find = anchor;
  
    cout << "Select from the menu  which formula you would like to use:\n";
    cout << " 1|\tADDITION / SUBTRACTION" << endl;
    cout << " 2|\tMULTIPLICATION / DIVISION" << endl;
    cout << " 3|\tz = nx OR z = n/x" << endl;
    cout << " 4|\tz = x/n OR z = 1/nx" << endl;
    cout << " 5|\tz = x^n " << endl;
    cout << " 6|\tz = x^(1/n) (nth root)" << endl;

    try
    {
	cin  >> select;

	switch (select)
	{
	    case 1:
	    {
		cout << "Enter the name of the first variable: " << endl;
		cin.ignore();
		getline(cin, var);
		while (find != end->link)
		{
		    if(find->name == var)
			n1 = find->absERR;
		    find = find->link;
		}
		find = anchor;
		cout << "Enter the name of the second variable: " << endl;
		cin.ignore();
		getline(cin, var);
		while (find != end->link)
		{
		    if(find->name == var)
			n2 = find->absERR;
		    find = find->link;
		}
		add->absERR = calcERR(n1,n2);
		add->relERR = calcRelERR(add->value,add->absERR);
		break;
	    }
	case 2:
	{
	    cout << "Enter the name of the first variabe:" << endl;
	    cin.ignore();
	    getline(cin, var);
	    while (find != end->link)
	    {
		if(find->name == var)
		    n1 = find->relERR;
		find = find->link;
	    }
	    find = anchor;
	    cout << "Enter the name of the second variabe:" << endl;
	    cin.ignore();
	    getline(cin, var);
	    while(find != end->link)
	    {
		if(find->name == var)
		    n2 = find->relERR;
		find = find->link;
	    }
	    add->relERR = calcERR(n1,n2);
	    add->absERR = calcAbsERR(add->value,add->relERR);
	    break;
	}
	case 3:
	{
	    cout << "Please enter the constant that is being multiplied:";
	    cin  >> constant;
	    find = anchor;
	    cout << "Please enter the name of your variable:";
	    cin.ignore();
	    getline(cin,var);
	    while(find != end->link)
	    {
		if(find->name == var)
		{
		    n1 = find->absERR;
		    value = find->value;
		}
		find = find->link;
	    }
	    add->absERR =  constant * n1;
	    add->relERR = calcRelERR(add->value, add->absERR);
	    break;
	}
	case 4:
	{
	    cout << "Please enter the constant to be used: ";
	    cin  >> constant;
	    cout << "Please enter the name of the variable to be used: ";
	    cin.ignore();
	    getline (cin, var);
	    find = anchor;
	    while (find != end->link)
	    {
		if (find->name == var)
		{
		    n1 = find->relERR;
		    value = find->value;
		}
		find = find->link;
	    }
	    add->relERR = constant * n1;
	    add->absERR = calcAbsERR(add->value,add->relERR);
	    break;
	}
	case 5:
	{
	    cout << "Please enter the constant to be used: ";
	    cin  >> constant;
	    cout << "Please enter the name of the variable to be used: ";
	    cin.ignore();
	    getline (cin, var);
	    find = anchor;
	    while (find != end->link)
	    {
		if (find->name == var)
		{
		    n1 = find->relERR;
		    value = find->value;
		}
		find = find->link;
	    }
	    add->relERR = constant * n1;
	    add->absERR = calcAbsERR(add->value,add->relERR);
	    break;
	}
	case 6:
	{
	    cout << "Please enter the constant to be used: " << endl;
	    cin  >> constant;
	    cout << "Please enter the name of the variable to be used: ";
	    cin.ignore();
	    getline(cin,var);
	    find = anchor;
	    while (find != end->link)
	    {
		if (find->name == var)
		{
		    n1 = find->relERR;
		    value = find->value;
		}
		find = find->link;
	    }
	    add->relERR = constant / n1;
	    add->absERR = calcAbsERR(add->value,add->absERR);
	    break;
	}
	}
    }
    catch(invalid_argument invArg)
    {
	cout << "INVALID ARGUMENT: " << invArg.what() << endl;
    }
}

float Error::calcAbsERR(double v, float r)
{
    return r*v;
}

float Error::calcRelERR(double v, float a)
{
    return a/v;
}

float Error::calcERR(float n1, float n2)
{
    float temp;
    temp = sqrt(n1*n1 + n2*n2);
    return temp;
}
void Error::deleteEntry()
{
    dataType *deleteEntry;
    deleteEntry = anchor;
    
    string s;

    cout << endl << "\tDELETING ENTRY . . ." << endl;
    if (anchor == NULL)
    {
	cout << "There is nothing to remove." << endl << endl;
	return;
    }
    cout << "Enter the name of the variable that you would like to delete:" << endl;
    cin.ignore();
    getline(cin,s);
    if (anchor->name == s)
    {
	anchor = deleteEntry->link;
	cout << s << " has been deleted from the list." << endl;
	return;
    }
    else
    {
	while (deleteEntry != NULL)
	{
	    
	    if (deleteEntry->link->name == s)
	    {
		if(deleteEntry->link->link != NULL)
		    deleteEntry->link = deleteEntry->link->link;
		else
		{
		    deleteEntry->link = NULL;
		}
		cout << s << " has been deleted from the list." << endl;
		return;
	    }
	    else
		deleteEntry = deleteEntry->link;
	}
    }
    cout << "ERROR: " << s << " was not found in the linked list." << endl;

}

void Error::displayTable()
{
    dataType *displayNode;
    displayNode = anchor;
    cout << endl << "\tDISPLAYING ERROR TABLE . . . " << endl << endl;
    if (anchor == NULL)
    {
	cout << "THERE ARE CURRENTLY NO ENTRIES." << endl << endl;
	return;
    }
    cout << scientific << showpoint << setprecision (2);
    cout << setw(15) << " NAME\t\t" << setw(4)<< " VALUE \t\t" << setw(4)
	 << "absERR \t\t" << setw(4) << " relERR" << endl;
    cout << " ------------------------------------------------------------------- "<< endl;
    while(displayNode != end->link)
    {
	cout << setw(15) << displayNode->name << "\t\t" 
	     << displayNode->value << "\t" << setw(4)
	     << displayNode->absERR << "\t" << setw(4)
	     << displayNode->relERR << endl;
	displayNode = displayNode->link;
    }
    cout << endl << endl;
}

void Error::exportTable()
{
    ofstream write;
    dataType *writeNode;
    writeNode = anchor;
    write.open("lab4ERROR.txt");
    write  << endl << "\tDISPLAYING ERROR TABLE . . . " << endl << endl;
    if (anchor == NULL)
    {
        write << "THERE ARE CURRENTLY NO ENTRIES." << endl << endl;
        return;
    }
    write << scientific << showpoint << setprecision (2);
    write << setw(15) << " NAME\t\t" << setw(4)<< " VALUE \t\t" << setw(4)
	  << "absERR \t\t" << setw(4) << " relERR" << endl;
    write << " ------------------------------------------------------------------- "<< endl;
    while(writeNode != end->link)
    {
        write << setw(15) << writeNode->name << "\t\t"
             << writeNode->value << "\t" << setw(4)
             << writeNode->absERR << "\t" << setw(4)
             << writeNode->relERR << endl;
        writeNode = writeNode->link;
    }
    write << endl << endl;
    write.close();
}
