
    CString csData;  
    CString csTemp;
    TChar sp;
    int nIndex = 0, nStart = 0;  
   
    while ( nIndex != -1 )  
    {  
        nIndex = str.Find( sp, nStart );
        if( nIndex != -1 )  
        {  
            csTemp = str.Mid( nStart, nIndex - nStart );
            nStart = nIndex + 1;
        }  
        else  
        {  
            csTemp = str.Mid( nLast, str.GetLength() - nLast );
        }  

        TRACE0(strTemp);   //   你可以在这将它插入到数组中去.  
  }

