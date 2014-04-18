set m0=23
set m1=230
set m2=2300
set m3=23000
set m4=230000
set m5=31
set m6=310
set m7=3100
set m8=31000
set m9=310000
set m10=1000000
               
set n0=604235199
set n1=563922877
set n2=861239407
set n3=560704847
set n4=941251117
set n5=706698887
set n6=712147925
set n7=694912855
set n8=546186413
set n9=1023309743
set n10=666329337136979687
                          
set k0=15                 
set k1=18
set k2=21
set k3=24
set k4=27
set k5=30
set k6=33
set k7=36
set k8=39
set k9=42
set k10=45

#(A) primes (+11 points, +1 points for each correct case)

	set srcdir=~csci531/public/cs531/hw7
	/bin/rm -f f?.pms f??.pms

        ./hw7 primes -n=$m0 > f0.pms
        ./hw7 primes -n=$m1 > f1.pms
        ./hw7 primes -n=$m2 > f2.pms
        ./hw7 primes -n=$m3 > f3.pms
        ./hw7 primes -n=$m4 > f4.pms
        ./hw7 primes -n=$m5 > f5.pms
        ./hw7 primes -n=$m6 > f6.pms
        ./hw7 primes -n=$m7 > f7.pms
        ./hw7 primes -n=$m8 > f8.pms
        ./hw7 primes -n=$m9 > f9.pms
        ./hw7 primes -n=$m10 > f10.pms

	foreach f (0 1 2 3 4 5 6 7 8 9 10)
		echo "==> $srcdir/f$f.pms"
		diff f$f.pms $srcdir/f$f.pms
	end

	/bin/rm -f f?.pms f??.pms

#(B) trialdiv (+20 points, +2 for each correct answer)

	set srcdir=~csci531/public/cs531/hw7
	/bin/rm -f f?.td

	set pf=$srcdir/primes.n223

	./hw7 trialdiv -n=$n0 -p=$pf > f0.td
	./hw7 trialdiv -n=$n1 -p=$pf > f1.td
	./hw7 trialdiv -n=$n2 -p=$pf > f2.td
	./hw7 trialdiv -n=$n3 -p=$pf > f3.td
	./hw7 trialdiv -n=$n4 -p=$pf > f4.td
	./hw7 trialdiv -n=$n5 -p=$pf > f5.td
	./hw7 trialdiv -n=$n6 -p=$pf > f6.td
	./hw7 trialdiv -n=$n7 -p=$pf > f7.td
	./hw7 trialdiv -n=$n8 -p=$pf > f8.td
	./hw7 trialdiv -n=$n9 -p=$pf > f9.td

	foreach f (0 1 2 3 4 5 6 7 8 9)
		echo "==> $srcdir/f$f.td"
		diff f$f.td $srcdir/f$f.td
	end

	/bin/rm -f f?.td

#(C) millerrabin (+22 points, +2 for each correct answer)

	set srcdir=~csci531/public/cs531/hw7
	/bin/rm -f f?.mr f??.mr

	set pf=$srcdir/primes.n223

	./hw7 millerrabin -n=$n0 -t=12 -p=$pf > f0.mr
	./hw7 millerrabin -n=$n1 -t=12 -p=$pf > f1.mr
	./hw7 millerrabin -n=$n2 -t=12 -p=$pf > f2.mr
	./hw7 millerrabin -n=$n3 -t=12 -p=$pf > f3.mr
	./hw7 millerrabin -n=$n4 -t=12 -p=$pf > f4.mr
	./hw7 millerrabin -n=$n5 -t=12 -p=$pf > f5.mr
	./hw7 millerrabin -n=$n6 -t=12 -p=$pf > f6.mr
	./hw7 millerrabin -n=$n7 -t=12 -p=$pf > f7.mr
	./hw7 millerrabin -n=$n8 -t=12 -p=$pf > f8.mr
	./hw7 millerrabin -n=$n9 -t=12 -p=$pf > f9.mr
	./hw7 millerrabin -n=$n10 -t=12 -p=$pf > f10.mr

	foreach f (0 1 2 3 4 5 6 7 8 9 10)
		echo "==> $srcdir/f$f.mr"
		diff f$f.mr $srcdir/f$f.mr
	end

	/bin/rm -f f?.mr f??.mr

#(D) rndsearch (+22 points, +2 for each correct answer)

        set srcdir=~csci531/public/cs531/hw7
	/bin/rm -f f?.rs f??.rs

	set pf=$srcdir/primes.n223
	set rf=$srcdir/rnd.220

	./hw7 rndsearch -k=$k0 -t=10 -p=$pf -r=$rf > f0.rs
	./hw7 rndsearch -k=$k1 -t=10 -p=$pf -r=$rf > f1.rs
	./hw7 rndsearch -k=$k2 -t=10 -p=$pf -r=$rf > f2.rs
	./hw7 rndsearch -k=$k3 -t=10 -p=$pf -r=$rf > f3.rs
	./hw7 rndsearch -k=$k4 -t=10 -p=$pf -r=$rf > f4.rs
	./hw7 rndsearch -k=$k5 -t=10 -p=$pf -r=$rf > f5.rs
	./hw7 rndsearch -k=$k6 -t=10 -p=$pf -r=$rf > f6.rs
	./hw7 rndsearch -k=$k7 -t=10 -p=$pf -r=$rf > f7.rs
	./hw7 rndsearch -k=$k8 -t=10 -p=$pf -r=$rf > f8.rs
	./hw7 rndsearch -k=$k9 -t=10 -p=$pf -r=$rf > f9.rs
	./hw7 rndsearch -k=$k10 -t=10 -p=$pf -r=$rf > f10.rs

	foreach f (0 1 2 3 4 5 6 7 8 9 10)
		echo "==> $srcdir/f$f.rs"
		diff f$f.rs $srcdir/f$f.rs
	end

	/bin/rm -f f?.rs f??.rs

#(E) maurer (+22 points, +2 for each correct answer)

        set srcdir=~csci531/public/cs531/hw7
	/bin/rm -f f?.ma f??.ma

	set pf=$srcdir/primes.n223
	set rf=$srcdir/rnd.220

	./hw7 maurer -k=$k0 -p=$pf -r=$rf > f0.ma
	./hw7 maurer -k=$k1 -p=$pf -r=$rf > f1.ma
	./hw7 maurer -k=$k2 -p=$pf -r=$rf > f2.ma
	./hw7 maurer -k=$k3 -p=$pf -r=$rf > f3.ma
	./hw7 maurer -k=$k4 -p=$pf -r=$rf > f4.ma
	./hw7 maurer -k=$k5 -p=$pf -r=$rf > f5.ma
	./hw7 maurer -k=$k6 -p=$pf -r=$rf > f6.ma
	./hw7 maurer -k=$k7 -p=$pf -r=$rf > f7.ma
	./hw7 maurer -k=$k8 -p=$pf -r=$rf > f8.ma
	./hw7 maurer -k=$k9 -p=$pf -r=$rf > f9.ma
	./hw7 maurer -k=$k10 -p=$pf -r=$rf > f10.ma

	foreach f (0 1 2 3 4 5 6 7 8 9 10)
		echo "==> $srcdir/f$f.ma"
		diff f$f.ma $srcdir/f$f.ma
	end

	/bin/rm -f f?.ma f??.ma


#Bad commandline : -1 point each for each not handling properly
                # need some sort of error output to indicate that the command
                #     cannot be completed, it does not have to exactly the
                #     error indicated below, just something reasonable to inform
                #     the user about the error condition
                # please note that commandline parsing is separate from
                #     other functionalities, so even though a student has
                #     declared that certain part of the assignments is not
                #     imlemented, commandling parsing still needs to be done
                #     for those commands
        set srcdir=~csci531/public/cs531/hw7
        ./hw7
        #            (malformed command)
        ./hw7 primes -n="foobar"
        #            (invalid maxval)
        ./hw7 primes -n
        #            (malformed command)
        ./hw7 primes -n=17825792
        #            (maxval is out of range)
		./hw7 trialdiv -n=foobar -p=$srcdir/primes.n220
        #            (invalid number)
		./hw7 trialdiv -n=4961 -p=xyzzy
        #            (invalid primesfile)
		set n0=1012897331475683
		set n1=787429
		./hw7 trialdiv -n=$n0 -p=$srcdir/primes.n220
        #            should output:
        #                n passes trial division test (not enough primes)
		./hw7 millerrabin -z=$n1 -t=20 -p=$srcdir/primes.n220
        #            (malformed command)
		./hw7 millerrabin -n=foobar -t=20 -p=$srcdir/primes.n220
        #            (invalid number)
		./hw7 millerrabin -n=$n1 -t=foobar -p=$srcdir/primes.n220
        #            (invalid maxitr)
		./hw7 millerrabin -n=$n1 -t=20 -p=xyzzy
        #            (invalid primesfile)
		./hw7 millerrabin -n=$n1 -t=20
        #            (missing primesfile)
		./hw7 rndsearch -k=40 -t=10 -z=primes.n220 -r=$srcdir/rnd.220
        #            (malformed command)
		./hw7 rndsearch -k=40 -p=$srcdir/primes.n220 -r=$srcdir/rnd.220
        #            (missing maxitr)
		./hw7 rndsearch -k=40 -t=10 -p=$srcdir/primes.n220
        #            (missing rndfile)
		./hw7 rndsearch -k=40 -t=10 -p=$srcdir/primes.n220 -r=xyzzy
        #            (invalid rndfile)
		./hw7 maurer -k=40 -z=$srcdir/primes.n220 -r=$srcdir/rnd.220
        #            (malformed command)
		./hw7 maurer -k=40 -p=$srcdir/primes.n220
        #            (missing rndfile)
		./hw7 maurer -k=40 -p=$srcdir/primes.n220 -r=xyzzy
        #            (invalid rndfile)
