//Copyright (c) 2018 Ultimaker B.V.
//CuraEngine is released under the terms of the AGPLv3 or higher.

#ifndef SKIRT_BRIM_H
#define SKIRT_BRIM_H

#include "utils/Coord_t.h"

namespace cura 
{

class Polygons;
class SliceDataStorage;

class SkirtBrim
{
public:
    /*!
     * Generate skirt or brim (depending on parameters).
     * 
     * When \p distance > 0 and \p count == 1 a skirt is generated, which has
     * slightly different configuration. Otherwise, a brim is generated.
     * 
     * \param storage Storage containing the parts at the first layer.
     * \param first_layer_outline The outline to generate skirt or brim around.
     * \param distance The distance of the first outset from the parts at the first
     * layer.
     * \param primary_line_count Number of offsets / brim lines of the primary extruder.
     * \param set to false to force not doing brim generation for helper-structures (support and ooze/draft shields)
     */
    static void generate(SliceDataStorage& storage);

    /*!
     * Generate the brim inside the ooze shield and draft shield
     * 
     * \warning Adjusts brim_covered_area
     * 
     * \param storage Storage containing the parts at the first layer.
     * \param[in,out] brim_covered_area The area that was covered with brim before (in) and after (out) adding the shield brims
     */
    static void generateShieldBrim(SliceDataStorage& storage, Polygons& brim_covered_area);

    /*!
     * \brief Get the reference outline of the first layer around which to
     * generate the first brim/skirt line.
     *
     * This function may change the support polygons in the first layer
     * in order to meet criteria for putting brim around the model as well as
     * around the support.
     *
     * \param extruder_nr The extruder for which to get the outlines. -1 to include outliens for all extruders
     * \return The resulting reference polygons
     */
    static Polygons getFirstLayerOutline(SliceDataStorage& storage, const int extruder_nr);

    static void generateSupportBrim(SliceDataStorage& storage, const bool merge_with_model_skirtbrim);

private:
    /*!
     * \brief Generate the skirt/brim lines around the model.
     * 
     * \param start_distance The distance of the first outset from the parts at
     * the first line.
     * \param primary_line_count Number of offsets / brim lines of the primary
     * extruder.
     * \param primary_extruder_minimal_length The minimal total length of the
     * skirt/brim lines of the primary extruder.
     * \param first_layer_outline The reference polygons from which to offset
     * outward to generate skirt/brim lines.
     * \param[out] skirt_brim_primary_extruder Where to store the resulting
     * brim/skirt lines.
     * \return The offset of the last brim/skirt line from the reference polygon
     * \p first_layer_outline.
     */
    static coord_t generatePrimarySkirtBrimLines(const coord_t start_distance, size_t& primary_line_count, const coord_t primary_extruder_minimal_length, const Polygons& first_layer_outline, Polygons& skirt_brim_primary_extruder);
};
}//namespace cura

#endif //SKIRT_BRIM_H
