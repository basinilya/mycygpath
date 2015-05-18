#include "mycygpath.h"

#include <iostream>
#include <unistd.h> /* for getopt(3) */
#include <stdlib.h> /* for mbtowc(3), exit(3) */
#include <sysexits.h>	/* for EX_* exit codes */
using namespace std;

// http://stackoverflow.com/a/8173726/447503
template <typename T> basic_istream<T>& appendline(basic_istream<T>& is, basic_string<T>& str, T delim = '\n')
{
    size_t size = str.size();
    size_t capacity = str.capacity();
    streamsize spaceRemaining = capacity - size;

    if (spaceRemaining == 0)
    {
        capacity = max(static_cast<size_t>(8), capacity * 2);
        spaceRemaining = capacity - size;
    }

    // give getline access to all of capacity
    str.resize(capacity);

    // get until delim or spaceRemaining is filled
    is.getline(&str[size], spaceRemaining, delim);

    // gcount includes the delimiter but not the null terminator
    size_t newSize = size + is.gcount();

    // is failbit set?
    if (!is)
    {
        // if string ran out of space, expand and retry
        if (is.gcount()+1 == spaceRemaining)
        {
            is.clear();
            str.resize(newSize);
            str.reserve(capacity * 2);
            return appendline(is, str, delim);
        }
    }
    else if (!is.eof())
        --newSize;

    // resize string to fit its contents
    str.resize(newSize);
    return is;
}

void usage(char *argv0) {
	cerr << "Usage: " << argv0 << " [-0] [-d delimiter]" << endl;
}

int main(int argc, char* argv[]) {
	UNICODE_STRING winstruct;

	wstring ws;
	wchar_t delim = '\n';

	setlocale(LC_ALL, "");

	int c;
	while ((c = getopt (argc, argv, "0d:")) != -1)
		switch(c)
		{
		case '?':
			usage(argv[0]);
			exit(EX_USAGE);
			break;
		case '0':
			delim = '\0';
			break;
		case 'd':
			mbtowc(&delim, optarg, MB_CUR_MAX);
			delim = optarg[0];
		break;
		}

	for(;;) {
		ws.clear();
		appendline(wcin, ws, delim);
		winstruct.Buffer = &ws[0];
		winstruct.MaximumLength = winstruct.Length = (ws.size() * sizeof(ws[0]));
		mycygpath(&winstruct, true);
		wcout << ws;
		if (wcin.good()) {
			wcout << delim;
		} else {
			break;
		}
	}
	wcout << flush;
	return 0;
}
