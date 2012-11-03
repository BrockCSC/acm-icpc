[![acm-icpc](http://acm.ashland.edu/Images/master.gif "ACM-ICPC ECNA")](http://acm.ashland.edu/)

### What is this?

A repository along with a [wiki](https://github.com/BrockCSC/acm-icpc/wiki) for the Brock ICPC team or students with interest in the ICPC.

Post your solutions, libraries, guides, tutorials, or anything you think is helpful.

**IMPORTANT**: I'm looking for someone (preferably at Brock) to adopt this project and maintain it. Please [contact me](http://dennisideler.com) if interested.

### Getting Started

Read the **[wiki](https://github.com/BrockCSC/acm-icpc/wiki)**. Anyone can edit the wiki.

#### Contributing
- Members of the *BrockCSC* organization have push and pull access, so you just need to clone this repo.
- Non-members will have to fork it and send a pull request.
- If you have no idea what any of that means, I suggest you read through the tutorials at http://help.github.com.
- Please
  - Place your solution in the appropriate location
  - Add a README that explains the strategy you used to solve the problem


It's generally neater to create a new branch for a new task and then merge it with the master branch upon completion.

For example, if you want to work on problem #101:

```
$ git checkout -b 101
... code up a solution and place it in the appropriate directory
$ git commit -am 'Add solution for 101'
$ git checkout master
$ git merge 101
$ git push origin
```

### Java Tips

- For your submission to an online judge to work, you must name your source file `Main.java` (but not during actual competition, then you must name it after the problem letter). Put everything inside this file, do not use separate files for classes.
- **Input** comes from `System.in`, **output** goes to `System.out`
- To **compile** your Java source file: `javac Main.java`
- To **run and test** your program: `java Main < input.dat`
- You can combine these for ease: `javac Main.java && java Main < input.dat`


### C++ Tips

- Name your source file after the problem number (in actual competition it needs to be after the problem letter).
- **Input** comes from `stdin` (`std::cin`), **output** goes to `stdout` (`std::cout`)
- To **compile** your C++ source file: `g++ 001.cc -o 001`
- Note that online judges will use these compiler options: `-lm -lcrypt -O2 -pipe -DONLINE_JUDGE`
- To **run and test** your program: `./001 < 001.dat`
- You can combine these for ease: `g++ 001.cc -o 001 && ./001 < 001.dat`

### General Tips

- Practice! It's the most effective way to improve.
  - Find problems [here](https://github.com/BrockCSC/acm-icpc/wiki/Online-Resources#wiki-practice).
  - You get the most out of practice if you imitate contest conditions.
- Identify the easier problems and solve those first.
  - Look at the live scoreboard to see which problems are quickly and often solved.
- Use multiple terminal windows. Having to close your editor every time to compile and run your program is slow.
- Choose your [printed notes](https://github.com/BrockCSC/acm-icpc/wiki/Online-Resources#wiki-books) wisely and know how/when to reference them.
- Don't debug at the computer. Print your code and switch spots with a teammate.
- You can break coding guidelines & styleguides for contest settings, so it's okay to use
  - GOTOs
  - structs
  - hard to read code (keep in mind a teammate will need to understand your code if you need help)
  - code templates that contain "ugly" code (e.g. `#define`, `typedef`)
  - global variables
  - public scope for everything
