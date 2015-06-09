from __future__ import print_function
import subprocess

def start_process(process_path):
    return subprocess.Popen(process_path, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

def assert_output(process, expected_output):
    actual_output = process.communicate()[0]
    if actual_output != expected_output:
        raise AssertionError('Expected "{0}" but was "{1}"'.format(
            expected_output, actual_output))


listener_1 = start_process('./listener')
listener_2 = start_process('./listener')
broadcaster = start_process('./broadcaster')

expected_output = 'DSC10HERE'

try:
    assert_output(listener_1, expected_output)
    assert_output(listener_2, expected_output)
except AssertionError as e:
    print(str(e))
    exit(1)

