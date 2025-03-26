from notopenai import NotOpenAI
import json

# Input the API key obtained for the lab
API_KEY = "blahblahblahnicetrybuddy"
CLIENT = NotOpenAI(api_key=API_KEY)

def get_response(prompt):
    chat_completion = CLIENT.chat.completions.create(
    messages=[
        {
            "role": "user",
            "content": prompt,
        }
    ],
    model="gpt-3.5-turbo", # the GPT model to use
    )
    response_str = chat_completion.choices[0].message.content
    return response_str

def check_result(generated_code, test_cases):
    """
    Check which test cases failed from the generated code
    generated_code - str
    test_caes - dict

    e.g., if the generated_code is:
    def fun(x):
        return x
    """
    exec(generated_code, globals())
    failed_cases = []
    for i in test_cases:
        input_value = i["input"]
        expected_output = i["expected_output"]
        res = factorial(input_value)
        if res != expected_output:
            failed_cases.append((input_value, res, expected_output))
    return failed_cases

def check_result_for_s(generated_code_for_s, test_cases_for_s):
    exec(generated_code_for_s, globals())
    failed_cases_for_s = []
    for i in test_cases_for_s:
        input_value = i["input"]
        expected_output = i["expected_output"]
        res = parse_csv(input_value)
        if res != expected_output:
            failed_cases_for_s.append((input_value, res, expected_output))
    return failed_cases_for_s
    

if __name__ == "__main__":
    generated_code = """
def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)
    """
    test_cases = [
        {"input": 3, "expected_output": 6},
        {"input": 4, "expected_output": 24},
    ]

    failed_cases = check_result(generated_code, test_cases)
    if failed_cases:
        for i in failed_cases:
            print(f"input: {i[0]}, output: {i[1]}, and expected output: {i[2]}")
    else:
        print("passed test cases")


    # ---------------------------------------------------------------------------------------------------

    s = '''Date,Character,Age,HeightCm,AppleCount,MoodRating
2025-01-15,Snow White,14,157.5,1,8.5
Doc,200,91.4,3,7.2
2025-01-16,Grumpy,199,89.0,0,3.4
2025-01-16,202,94.0,2,9.7
2025-01-17,Sleepy,202,90.2,1,6.3
Bashful,198,88.5,1,5.8
2025-01-18,Sneezy,197,92.3,2,7.4
2025-01-18,Dopey,195,87.1,4,8.9
2025-01-19,,42,175.6,0,2.1
Prince,25,185.3,2,9.5
2025-01-20,Huntsman,38,178.4,1,6.7
2025-01-20,250,92.0,3,7.3
2025-01-21,Forest Animals,5,30.5,4,9.2'''

    generated_code_for_s = """
import csv
from io import StringIO

def parse_csv(s):
    # Create a StringIO object to treat the CSV string as a file
    csv_file = StringIO(s)

    # Use csv.DictReader to read the CSV string and convert it to a dictionary
    reader = csv.DictReader(csv_file)

    # Convert the reader object to a list of dictionaries
    data = [row for row in reader]

    # Convert the list of dictionaries to a dictionary of dictionaries
    result = {row['Date']: {k: v for k, v in row.items() if k != 'Date'} for row in data}

    return result
"""

    test_cases_for_s = [
        {
            "input": s,
            "expected_output": {
                "2025-01-15": {"Character": "Snow White", "Age": 14, "HeightCm": 157.5, "AppleCount": 1, "MoodRating": 8.5},
                "Doc": {"Date": "2025-01-15", "Age": 200, "HeightCm": 91.4, "AppleCount": 3, "MoodRating": 7.2},
                "2025-01-16": {"Character": "Grumpy", "Age": 199, "HeightCm": 89.0, "AppleCount": 0, "MoodRating": 3.4},
            }
        }
    ]

    failed_cases_for_s = check_result_for_s(generated_code_for_s, test_cases_for_s)
    if failed_cases_for_s:
        for i in failed_cases_for_s:
            print(f"input: {i[0]}, output: {i[1]}, and expected output: {i[2]}")
    else:
        print("passed test cases for s")