// Multi-Threaded Prime-Finder CPU Benchmark
// Author: Lieutenant Debaser
// This benchmark works by calculating the number of primes between zero and an upper limit on multiple
// simultaneous threads.

#include <iostream>
#include <vector>
#include <thread>
#include <sstream>
#include <string>

#define THREAD_LIMITER 4   // <= Change to set the upper limit on the number of threads that can be used

void parse_cli (int argc, char* argv [], int& upper_limit, int& thread_count);
bool print_help (int argc, char* argv []);
void calculate_primes (unsigned int upper_limit, int thread_id);

int main (int argc, char* argv []) {
    // Declare variables used for the multithreaded benchmark
    int upper_limit = 10000;
    int thread_count = 2;
    std::vector <std::thread*> thread_list;
    bool do_benchmark = true;

    // Test for command line arguments
    if (argc > 1) {
        switch (argc % 2) {
            case 0:
                do_benchmark = !(print_help (argc, argv));
                break;
            case 1:
                parse_cli (argc, argv, upper_limit, thread_count);
        }
    }

    if (do_benchmark) {
        // Create number of threads specified and launch them
        for (unsigned int i = 0; i < thread_count; i++) {
            thread_list.push_back (new std::thread (calculate_primes, upper_limit, i));
        }

        // Wait for threads to finish so they can be joined
        for (unsigned int i = 0; i < thread_count; i++) {
            thread_list [i]->join ();
        }

        // Delete all created threads
        for (unsigned int i = 0; i < thread_count; i++) {
            delete thread_list [i];
        }
    }

    // Trailing newline for readability on the terminal
    std::cout << '\n';

    return 0;
}

// Parse the command line arguments to see if any specific parameters have been issued by the user
void parse_cli (int argc, char* argv [], int& upper_limit, int& thread_count) {
    // Declare variables needed for the function
    std::stringstream conversion_stream;
    std::string temp_string = "";
    int temp_int = 0;

    // Check each element of argv to see if it is a valid argument
    for (int i = 1; i < argc; i++) {
        conversion_stream << argv [i];
        conversion_stream >> temp_string;
        conversion_stream.clear ();
       
        // The number of threads to use has been specified 
        if (temp_string == "--threads") {
            conversion_stream << argv [i + 1];
            conversion_stream >> temp_int;
            thread_count = temp_int;

            // Check safeguard to ensure a large number of threads were not issued
            if (thread_count > THREAD_LIMITER) {
                std::cout << "\nWarning: " << thread_count << " is larger than the specified thread count limit of "
                    << THREAD_LIMITER << ". Only " << THREAD_LIMITER << " threads will be used."
                    << "\n\tTo change this, change the THREAD_LIMITER definition at the top of the source code.\n";
                thread_count = THREAD_LIMITER;
            }
            i++;    // Skip past integer already handled
        }

        // The upper limit to stop calculating at has been specified
        else if (temp_string == "--limit") {
            conversion_stream << argv [i + 1];
            conversion_stream >> temp_int;
            upper_limit = temp_int;
            i++;    // Skip past integer already handled
        }

        // An unknown argument has been issued
        else {
            std::cerr << "\nUnknown argument: " << temp_string
                << "\nUse argument --help for more information.";
            break;
        }

        conversion_stream.clear ();
    }
}

// Print the help message if --help has been issued
bool print_help (int argc, char* argv []) {
    bool success = false;

    if (argc == 2) {
        std::stringstream check_help;
        std::string temp_string = "";

        check_help << argv [1];
        check_help >> temp_string;

        if (temp_string == "--help") {
            std::cout << "\nMultithreaded Prime-Finder Benchmark"
                << "\nAvailable Commands:"
                << "\n\t--threads [count]"
                << "\n\t\tNumber of threads that will be used for the benchmark."
                << "\n\t\t(Current maximum threads that can be used for program is " << THREAD_LIMITER << ")"
                << "\n\t--limit [stop at]"
                << "\n\t\tDefines upper range limit for calculations."
                << "\n\t\t(i.e. --limit 10000 will calculate all primes between 0 and 10000)"
                << '\n';

            success = true;
        }
    }

    return success;
}

// Calculate prime numbers between 0 and the upper limit specified
void calculate_primes (unsigned int upper_limit, int thread_id) {
    // Variables used for prime number calculation
    std::vector <unsigned int> prime_nums;
    unsigned int num = 1;
    bool failed = false;

    // Calculate primes until the upper limit has been reached
    while (num <= upper_limit) {
        // Determine if the number is a prime
        for (int i = 1; i < prime_nums.size (); i++) {
            if (num % prime_nums [i] == 0) {
                failed = true;
                break;
            }
        }

        // If number was a prime, place it in vector containing prime numbers
        if (failed == false)
            prime_nums.push_back (num);

        // Increment counter by 2 (even numbers are never prime) and reset flag for next test
        num += 2;
        failed = false;
    }

    // Print a notifiicaiton stating which thread counted how many primes within a given range
    std::cout << "\nTHREAD ID " << thread_id << ": \n\tCalculated " << prime_nums.size () << " prime numbers between "
        << "0 and " << upper_limit << ".\n";
}
