# CFL Reachability

The CFL Reachability problem involves determining whether there is a path in a graph where the concatenation of edge labels along the path forms a string that belongs to a given context-free language. This problem extends the standard graph reachability problem to handle context-free languages, making it more expressive and suitable for a range of applications in program analysis.

This program executes and returns all the reachable pairs of the Graph for a CFG(Context Free Grammer).

## Build and Run

```sh
cd src
./run.sh ../data/example_input.txt
```

## Input Files and Format

To put the input, we need to consider the Edged labeled Graph. Add the input graph on the `../data/example_input.txt` file. The format:
```
0 a 1
1 b 2
2 b 3
3 b 4
```

Now, we also need the Grammer. Remember that, we are assuming that, the input Grammer is in CNF (Chomskey Normal Form). The format is:
```
ALPHABET:
a, b ;
VARIABLES:
S, A, B ; 
PRODUCTIONS:
S->AB
A->BB|a
B->AB|b
```

## Algorithmic Discussions

Here, we are considering the concatenation of edges of the Graph using DFS. Then we are calculating the CYK algorithm to determine the membership of
string if it is a member of the given CFG.

The implementation wise the algorithm might not be very efficient. It is running on O(n^3) time complexity for CYK algorithm.

The reference papers are given in link below:
1. https://cs.au.dk/~pavlogiannis/publications/papers/siglog_news22.pdf
2. https://dominoweb.draco.res.ibm.com/reports/rc24126.pdf
3. https://yuleisui.github.io/publications/ase23.pdf
4. https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=17376e6db0fae8b1aff5e10174fff0c5fae54bc7
5. https://cliplab.org/jd1mOkw/SAS2023/142840229/142840229.pdf

