# Code Timer class

This is a very simple RAII based timing mechanism that I have been using for years. It let's you time functions or blocks of code by simply declaring a variable of type Timer

Example:
    
    int sumVector(std::vector<int> &v)
    {
      Timer t("Sum");
      int ret = 0;
      for(int i: v)
      {
        ret += i;
      }
      
      return ret;
    }


The constructor takes a string tag that identifies the function or block being timed. When it goes out of scope, it adds the elapsed to the cumulative elapsed time for that block tag, and also keeps count of how many times that block executed (so average time can be calculated)

At the end of main()  you can call the static function Timer::dump() to display a summary like this:

    Name                    Count                   Time(ms)                Average(ms)
    -----------------------------------------------------------------------------------
    Test Add                        10                      458                     45
    Test Mul                        10                      3403                    340 
    
    
You can use the macro TIME_IT to automatcally use the current function name for the Timer tag like so:

    unsigned int testMul()
    {
      TIME_IT;
      unsigned int x = 1;
      for(int i = 0; i < N; ++i)
      {
        x *= i;
      }
      
      return x;
    }
    
Note that since it uses a map and static variables to keep track, it is not advisable to use this if the timed block is called thousands of times. The Timer object itself will introduce a bottleneck in such cases.

Also you may need to use dummy blocks or do {} while(0) constructs if you want to time a chunk of code thats not in a block.

Nevertheless, I have used this extensively to quickly instrument my code and detect bottlenecks. In fact I put TIME_IT on every function of note and before final release, just change its definition to a dummy no-op.

 
