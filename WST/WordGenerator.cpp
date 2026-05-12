#include "WordGenerator.hpp"
#include <cstdlib>
#include <algorithm>
#include <vector>

WordGenerator::WordGenerator(Difficulty difficulty) {
    initializeWords(difficulty);
}

void WordGenerator::initializeWords(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy:
            words_ = {
                "water", "sky", "grass", "hand", "foot", "table", "chair", "window", "door", "wall",
                "floor", "ceiling", "light", "shadow", "sound", "color", "taste", "smell", "day", "night",
                "morning", "evening", "winter", "summer", "spring", "autumn", "friend", "enemy", "brother", "sister",
                "mother", "father", "son", "daughter", "home", "garden", "park", "forest", "field", "river",
                "sea", "mountain", "hill", "pit", "path", "step", "trace", "sign", "flag", "horse"
            };
            break;
        case Difficulty::Medium:
            words_ = {
                "person", "animal", "plant", "building", "street", "square", "city", "country", "continent", "planet",
                "star", "galaxy", "universe", "time", "space", "matter", "energy", "information", "knowledge", "wisdom",
                "science", "art", "culture", "history", "geography", "biology", "chemistry", "physics", "mathematics", "literature",
                "music", "painting", "sculpture", "architecture", "theater", "cinema", "photography", "dance", "sport", "game",
                "work", "rest", "holiday", "weekday", "family", "society", "state", "law", "right", "freedom"
            };
            break;
        case Difficulty::Hard:
            words_ = {
                "existentialism", "transcendental", "conceptualization", "paradigm", "synergy", "epistemology", "ontology", "deconstruction", "postmodernism", "hermeneutics",
                "phenomenology", "identification", "authentication", "authorization", "encapsulation", "polymorphism", "inheritance", "abstraction", "virtualization", "containerization",
                "microservices", "monolith", "orchestration", "choreography", "asynchrony", "synchronization", "parallelism", "concurrency", "determinism", "stochasticity",
                "fractal", "attractor", "bifurcation", "entropy", "negentropy", "simulacrum", "hyperreality", "discourse", "narrative", "archetype",
                "quantum", "relativistic", "thermodynamics", "electrodynamics", "hydrodynamics", "aerodynamics", "chromodynamics", "geometry", "algebra", "topology"
            };
            break;
    }
}

std::string WordGenerator::generate(int word_count) {
    std::string result;
    prev_index_ = -1;

    if (words_.empty()) {
        return "Dictionary is empty.";
    }

    for (int i = 0; i < word_count; i++) {
        int new_index;
        do {
            new_index = std::rand() % words_.size();
        } while (new_index == prev_index_ && words_.size() > 1);

        result += words_[new_index];
        if (i < word_count - 1) result += " ";

        prev_index_ = new_index;
    }

    return result;
}

void WordGenerator::reset() {
    prev_index_ = -1;
}