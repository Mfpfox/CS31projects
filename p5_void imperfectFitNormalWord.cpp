


void imperfectFitNormalWord(const char a[], const int lineLength, int& remainingOnLine, ostream& outf, int tokenSize)
{
    //remaining set to linelength currently
    //tokenSize not changed
    int i = 0;
    while(a[i] != '\0')
    {
        for(int j = i; j < lineLength && a[i] != '\0'; j++) //i will be at correct position to continue on next line
        {
            outf << a[i];
            remainingOnLine--;
            tokenSize--;
        }
        //added as much of token to first line: either broke out because end of line or at zerobyte
        if(remainingOnLine == 0 && tokenSize != 0) //not done adding word
        {
            outf << endl;
            remainingOnLine = lineLength;
            continue;
        }
        else if(remainingOnLine == 0 && tokenSize == 0) //done adding word, fit perfectly on last line
        {
            outf << endl;
            remainingOnLine = lineLength;
            return;
        }
        else if (remainingOnLine > 0 && tokenSize == 0)
        {
            outf << ' ';
            remainingOnLine--;
            return;
        }
        
        
    }//end of while
}
