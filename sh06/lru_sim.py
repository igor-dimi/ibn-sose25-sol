import sys

def print_frame_state(step, page, frames, action):
    print(f"Step {step:2}: Page {page:2} → {action:6} | Frames: {frames}")

def simulate_lru(num_frames, access_sequence):
    frames = []
    lru_order = []  # Tracks least to most recently used pages

    for step, page in enumerate(access_sequence, 1):
        if page in frames:
            action = "Hit"
            # Move page to most recently used
            lru_order.remove(page)
            lru_order.append(page)
        else:
            action = "Fault"
            if len(frames) < num_frames:
                # Free space available
                frames.append(page)
            else:
                # Evict least recently used page
                lru_page = lru_order.pop(0)
                index = frames.index(lru_page)
                frames[index] = page
            lru_order.append(page)
        print_frame_state(step, page, frames.copy(), action)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python lru_sim.py <num_frames> <page1> <page2> ...")
        sys.exit(1)

    try:
        num_frames = int(sys.argv[1])
        access_sequence = list(map(int, sys.argv[2:]))
    except ValueError:
        print("Error: All inputs must be integers.")
        sys.exit(1)

    simulate_lru(num_frames, access_sequence)
