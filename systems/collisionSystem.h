/**
* Instead of asking enetites to check on each other for collison,
 * two major overhaul:
 *
 *  1.  the collision system accesses and changes data in current scene
 *      and determine if two objects are adjacent, signify to the objects
 *      in question that they have collision adjacent to each other,
 *      each object then disable movement in that direction
 *
 *  2. The collision system also updates the position each frame of all entities
 *
 * The functionality is achieved by collision system keeping a dictionary
 * of pointers pointing to all entities which are active in a scene
 * each update() call, the each entity sends a query to collision system
 * asking about their ambience (thus the move function shld really be
 * check and move function), if there is no obstruction, proceed, if
 * collision system indicates that there is an object in the way, disallow
 * movement in that specific direction
 *
 * there are only three states in the map/associated with entities:
 *  1.  inactive entity/intangible, meaning no obstruction, no colllision
 *      they simply are not registered by the collision system, like
 *      proper ghosts!
 *  2.  resistance, like grass, which means this entity can overlap in
 *      coordinate space with an obstructing entity, but only an obstructing
 *  3.  blocking entity, which can only overlap with resistance entities
 *
 *  Note that ai plotted movement will not have to obey collision system referee
 *  as they already have it in mind
 *
 *  collision system does not have to have any header and all others access it.
 *  it is just a very amiable arithmetician always called by others and never
 *  bothers other people. The most it does is use forward type declaration to help track people
 *
 *  Note that when we render, we render blocking entity then non blocking to create "hidden by grass" effect
*/
#ifndef collision
#define collision

#include <unordered_map>
#include <vector>   //it just makes life easier
#include <iostream>



struct pairHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &pair) const {
        // Hash both integers and combine them
        std::size_t hash1 = std::hash<T1>{}(pair.first);
        std::size_t hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ (hash2 << 1); // Combine hashes
    }
};



class Entity;   //forward declaration. the collision system will never directly interfere with
                    //an entity, but an entity will use it to keep track of others!
class CollisionSystem{
public:
    /**
     * key: a pair of int for coordinate of all entities, rounded up ints
     * value:   a pair of first the solid object, second the non-solid,
     *          the two objects are also rendered in first-second order
     * Note that a first occupancy entity is treated as solid
     * the second non-solid
     * once occupied, the coordinate blocks all others
     */
    std::unordered_map<std::pair<int, int>, std::pair<Entity*, Entity*> , pairHash> occupancyMap;

    /**
     * it takes the map data and populate the occupancyMap one by one
     * do not bother to check edge of the map;
     * todo: checking map edge will be future work
     * @param mapData is the vector of a vector of ints, a 2d array, we also render in this order (left right top bottom)
     */
    CollisionSystem(std::vector<std::vector<int>> & mapArr){    //use reference, should be a good idea
        int i, j;
        for(i;i<mapArr.size();i++){
            for(j; j<mapArr[i].size();j++){
                occupancyMap[std::pair(i,j)] =  std:: pair(nullptr, nullptr);
                //initialize all to be null pointer
            }//tested. Tentatively works ok
        }
    };

    //given a proposed location of movement (rounded up int)
    //check if it is ok. If not, return false.
    bool allowMovement(std::pair<int, int> key) {
        auto it = occupancyMap.find(key);
        if (occupancyMap.end() != it) {  //have a match
            return (nullptr == it->second.first);   //iterator pointer has first ask key, second as val
            //then, within val, first is the first occupant, blocking
            //if this is null, we good
        }return true;  //didn't find a match we good
    }
    void addBlockingEntity(std::pair<int, int> coord, Entity* blockingEntity){
        if(!allowMovement(coord)){std::cerr<<
            "attempt at adding blocking entity at: "<<
            coord.first<<" "<<coord.second<<
            " and it is already occupied !"<<std::endl;
            return;
        }else{
            occupancyMap[coord].first = blockingEntity; //blocking entity go to first
        }
    }

    /**
     * Do not bother to check if there already is an entity; we can overlap
     * @param coord int coordinate of where to add
     * @param nonBlockingEntity the entity which does not block other entities
     */
    void addNonBlockingEntity(std::pair<int, int> coord, Entity* nonBlockingEntity){
            occupancyMap[coord].second = nonBlockingEntity; //blocking entity go to first
    }

    void removeBlockingEntity(std::pair<int, int> coord){
        if(allowMovement(coord)){std::cerr<<
           "attempt at removing blocking entity at: "<<
           coord.first<<" "<<coord.second<<
           " and there is no blockingentity here !"<<std::endl;
            return;
        }else{
            occupancyMap[coord].first = nullptr; //blocking entity removed from collision system
        }
    }

    /**
     * we do not bother to write a method to remove non-blocking entities
     * if a non blocking isn't there, implied it is destroyed
     * we simply either desactivate it (stop rendering and updating)
     * or adjust its appearance and set blocking power to zero (i.e. burnt wheat field)
     * Because ultimately the only thing non blocking affords us
     * is that it slows down another passing entity, or makes world interactions
     * neither is a concern here.
     */
};

#endif