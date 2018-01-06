
For Question:1

-> To run code, run following commands on terminal:
	-]  gcc q1.c -lpthread
	-]  ./a.out

-> Input Format:-
	n (Number of post as well as number of readers)

-> Implementation:

	-> I am taking n as input where n is number of readers as well number of post.

	-> I am creating n+1 threads ( n - readers and 1 - writer )

	-> Reader ( Consumer ) thread will call consumer function and Writer ( Producer ) thread will call Producer function. For each thread I
		have a mutex therefore whenever someone access block ( post ) then no one can access it.After writer can access block writer will Write
		a post and reader can read it.



For Question:2

-> To run code, run following commands on terminal:
	-]  gcc q2.c -lpthread
	-]  ./a.out

-> Input format:-
	n (Number of numbers)
	n numbers (to sort).

-> Report:-

I have wrote two merge sort.
	-> Simple Merge sort
	-> Concurrent Merge sort

Then I run both code multiple times . I found different output then expected.
	-> My expectation was Concurrent Merge sort would run faster because of shared memory.

	-> I found that Simple Merge sort is running faster.

	-> Then I found that Simple Merge sort should run faster because of following reasons.
			-> concurrent Merge sort is accessing left array and right array simultaneously.

			-> When concurrent Merge sort is accessing left array, left array is loaded into cache memory. Then Concurrent Merge sort tries to
				 access right array then cache miss would happen . Because of cache miss multiple times, execution of code slows down.

			-> But in Simple Merge sort, 2 or 3 elements of left and right array is accessing at a time. therefore that elements can stay in
				 cache and retrieval time of those elements is much lesser than retrieval time of elements in concurrent merge sort.




For Question:3

-> To run code, run following commands on terminal:
	-]  gcc q3.c -lpthread
	-]  ./a.out

-> Input Format:-
	n (Number of Booth)
	Next n+1 lines:-
	(Number of voters) (Number of EVM) (max capacity of each EVM )

-> Implementation:-
	-> I am creating thread for each EVM and each voter.

	-> Voter thread will call voter function which will wait until he will allocate a EVM to vote.

	-> EVM thread will call EVM function. EVM function will generate a random number between 1 to max. capacity of that booth and allocate
		 that many voter to that EVM. Now EVM thread will give signal to voter thread that voter is a given that EVM to vote then after
		 Voting is done , Voter thread will terminate .After all voter of that booth is done then each EVM thread will terminate.
