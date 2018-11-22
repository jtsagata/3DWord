# 3D Word

Note this is a quick and dirty implementation. It is not as simple as it can be
(for a problem of that size the OOP is an overkill), and not as complex if it was
a real problem. However, the design is done so it can refactored to a real solution.

The program can be used as a small interpreter also. This makes it more pleasant to
use and help in testing. See the scripts folder for some scripts. Or you can just type
the commands in the program's prompt. (And i dont like prompts like 'Enter robot speed'

Also the CMake system can do source formating using clang-format, and also create
the distribution arhive (without CPACK to keep things simple).

If there more time was given, or if this was a real problem then a few things ought
to be done differently.

## Testing
```
$ RobotWorld
$ RobotWorld < scripts/script_name
```

##  Software methodology

1. Use a proper TDD development cycle with testing and refactoring
2. Document code with something like doxygen
3. Spend more than a few minutes in the design phase.

## Implementation

1. Install a testing library like gtest
2. Use dependency management with a cmake tool like conan (for gtest, boost ...)
3. Better class design
4. Real word simulation and real newtonial mechanics
5. Real language with lex and yacc

The Simulation class breaks the SRP principle. It do allot and have many reasons to
change. A proper implementation will need a Word class (to provide the time among others)
an Actor class (many robots or other types of actor possible) and a motion planner class.


