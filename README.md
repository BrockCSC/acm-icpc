![acm-icpc logo](https://cloud.githubusercontent.com/assets/497458/12186297/5296b5a8-b599-11e5-87b0-014c7b01b9db.png)

### What is this?

A repository along with a [wiki](https://github.com/BrockCSC/acm-icpc/wiki) for the Brock ICPC team or students with interest in the ICPC.

Post your solutions, libraries, guides, tutorials, or anything you think is helpful.

**IMPORTANT**: I'm looking for someone (preferably at Brock) to adopt this project and maintain it. Please [contact me](http://dennisideler.com) if interested. This repo could use some cleaning and a lot more solved problems.

### Getting Started

1. Subscribe to the [Brock ACM-ICPC mailing list](https://groups.google.com/d/forum/brock-acm-icpc).
2. Read the **[wiki](https://github.com/BrockCSC/acm-icpc/wiki)**. Anyone can edit the wiki.

#### Contributing
- Members of the *BrockCSC* organization have push and pull access and just need to clone this repo.
- Non-members will have to fork it and send a pull request.
- If you have no idea what any of that means, read through the tutorials at http://help.github.com.
- Bonus points if you explain how you solved the problem


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
- Have one person type up all sample input and I/O code beforehand, while the
  others look at the problem set.
- Know each other's strengths and weaknesses. Consider specialized roles vs multipurpose.
- Communicate with your teammates, but don't distract them.
- Don't get tunnel vision. If you get stuck on a problem, have a teammate look
  at it or attempt another problem if there is enough remaining time.
- Practice writing actual, compilable code on paper. Avoid pseudocode.
  It will save you a lot of time.
- Choose your [printed notes](https://github.com/BrockCSC/acm-icpc/wiki/Online-Resources#wiki-books) wisely and know how/when to reference them.
- Don't debug at the computer. Print your code and switch spots with a teammate.
- You can break coding guidelines & styleguides for contest settings, so it's okay to use
  - GOTOs
  - structs
  - hard to read code (keep in mind a teammate will need to understand your code if you need help)
  - code templates that contain "ugly" code (e.g. `#define`, `typedef`)
  - global variables
  - public scope for everything
