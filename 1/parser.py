import sys 
import matplotlib.pyplot as plt

def get_trace(trace):
    with open(trace) as file:
        lines = [line.rstrip() for line in file]
    return lines

def parse_instructions(instructions, window_size):
    idx = 0
    sequences = {}
    
    while (idx + window_size < len(instructions)):
        key = ""
        for inst in instructions[idx:idx+window_size]:
            key += inst + " "
         
        sequences[key] = sequences.get(key, 0) + 1
        idx += window_size

    return sequences

def draw_bar_gist(seqs, hits):
    fig = plt.figure(figsize=(18, 12))
    plt.bar(seqs, hits)

def main():
    if (len(sys.argv) != 3):
        print("Usage: python3 parser.py <trace> <instruction window size>")
        return

    trace = sys.argv[1]
    window_size = int(sys.argv[2])

    instructions = get_trace(trace)
    sequences = parse_instructions(instructions, window_size)

    sequences = {k: v for k, v in sorted(sequences.items(), key=lambda x: x[1])}
    
    seqs = [seq for seq in sequences.keys()]
    hits = [hit for hit in sequences.values()]

    draw_bar_gist(seqs, hits)
    plt.show()

if __name__ == '__main__':
    main() 
