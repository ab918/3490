**Note:** B = bruteforce, H = Horspool, M = Boyer&Moore

words	        Brute Force	    Horspool     B&M		B:	       H:	           M
relationship	3296579	        378826	    374787		1  :  0.114914886  :  0.113689676
University	    3296511         432732	    430201		1  :  0.131269697  :  0.130501916
published	    3296582	        455404	    447570		1  :  0.138144296  :  0.135767895
planning	    3296583	        475989	    472637		1  :  0.144388599  :  0.143371788
collected	    3296582	        448031	    441112		1  :  0.135907737  :  0.133808897
bringing	    3296583	        465778	    464967		1  :  0.141291149  :  0.141045137
assessment	    3296581	        412002	    395426		1  :  0.124978576  :  0.119950336
governmental	3296579	        383539	    378404		1  :  0.11634455   :  0.114786875
covid19	        3296584	        511538      511294	    1  :  0.155172142  :  0.155098126
alumni	        3296585	        624533	    610045	    1  :  0.189448475  :  0.185053624
							
							
average B	:  average H	:  average M					
3296574.9	:  458837.2	    :  452644.3												
1	        :  0.139186038	:  0.137307452					


As it can be seen there is a large difference in the times between bruteforce and the other two methods by magnitude of 7.18 bigger than horspool and a magnitude 7.28 times bigger than Boyer and Moore on average
It can also be noted that the there is a difference between the horspool and Boyer & Moores as Booyer&Moore is 1.01 times smaller then horspool on average.

INSTRUCTIONS:
* to make the all the .out files type in : 
    make
* to remove all the .out files type in :
    make clean

* to run all the Q1 questions type in :
    ./Q1 "<String>"
* to run the individually type in :
    ./P11 <filename> <"String">
    ./P12 <filename> <"String">

* to run all the Q2 questions type in :
    ./Q2 <"String">
* to run the individually type in:
    ./P21 <filename> <"String">
    ./P22 <filename> <"String">
    ./P23 <filename> <"String">
