#include "../../code/android_objectives.h"
#include <cassert>
#include <cstring>
int main()
{
    assert(std::strcmp(Android_Spanish_Objective(6, "Objective 3: Destroy all Nod forces in the area."), "Objetivo 3: Destruye todas las fuerzas del Nod en la zona.") == 0);
    assert(std::strcmp(Android_Spanish_Objective(25, "Objective 1: Locate the crashed UFO and retrieve Kane's artifacts from inside. "), "Objetivo 1: Localiza el ovni estrellado y recupera los artefactos de Kane de su interior.") == 0);
    assert(std::strcmp(Android_Spanish_Objective(6, "Objective Three: Destroy all Nod forces in the area."), Android_Spanish_Objective(6, "Objective 3: Destroy all Nod forces in the area.")) == 0);
    assert(std::strstr(Android_Spanish_Objective(20, "****ESTABLISHING BATTLEFIELD CONTROL****..........Standby!"), "ESTABLECIENDO") != nullptr);
    assert(std::strstr(Android_Spanish_Objective(251, "First Objective: Get an Engineer into the Temple of Nod to retrieve part of CABAL's core."), "Objetivo 1:") != nullptr);
    assert(std::strstr(Android_Spanish_Objective(389, "First Objective: Use your commander to warn the"), "Objetivo 1:") != nullptr);
    assert(std::strcmp(Android_Spanish_Objective(390, "CIVILIANS."), "CIVILES.") == 0);
    assert(std::strstr(Android_Spanish_Objective(393, "First Objective: Destroy all of CABAL's HARVESTERS,"), "COSECHADORAS,") != nullptr);
    assert(std::strcmp(Android_Spanish_Objective(394, "REFINERIES, and SILOS."), "REFINER\303\215AS y SILOS de CABAL.") == 0);
    assert(std::strstr(Android_Spanish_Objective(411, "Third Objective: Assassinate Tratos."), "Asesina a Tratos") != nullptr);
    assert(std::strstr(Android_Spanish_Objective(283, "Warning: Do not kill civilians or mutants!"), "No mates") != nullptr);
    assert(std::strstr(Android_Spanish_Objective(382, "ARCHAEOLOGIST killed!"), "muerto") != nullptr);
    assert(std::strstr(Android_Spanish_Objective(248, "A piece of CABAL's core has been recovered."), "recuperado") != nullptr);
    assert(std::strstr(Android_Spanish_Objective(83, "Now get an engineer over here to fix this bridge and I"), "Hassan") == nullptr);
    assert(std::strstr(Android_Spanish_Objective(84, "will alert Hassan to their presence."), "Hassan") != nullptr);
    assert(std::strstr(Android_Spanish_Objective(247, "Solomon: Change of plans - We have verified Vega's presence in the pyramid. CAPTURE the pyramid with Vega alive. DO NOT DESTROY IT!"), "NO LA DESTRUYAS") != nullptr);
    char const * custom = "Protect the allied Nod forces.";
    assert(Android_Spanish_Objective(6, custom) == custom);
    char const * translated = "Objetivo 3: Protege la base.";
    assert(Android_Spanish_Objective(6, translated) == translated);
    assert(Android_Spanish_Objective(9999, custom) == custom);
    assert(Android_Spanish_Objective(6, nullptr) == nullptr);
}
