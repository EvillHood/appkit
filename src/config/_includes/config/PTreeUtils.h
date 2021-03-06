/**
 * @file
 * @brief PoropertyTreeUtils. Declaration
 *
 *
 * $Id: $
 *
 **/

#pragma once

#include <boost/property_tree/ptree_fwd.hpp>

#include <set>
#include <string>

namespace appkit
{

namespace config
{

/**
 * Validate ptree by keys.
 * This function check ptree on the appropriate keys.
 * @ptree - verifiable tree.
 * @keys - unique keys collection.
 * @return void.
 * @throw exception::InvalidConfigEntry with bad entry list if the validate
 * fails.
 */
void validate(
    const boost::property_tree::ptree& ptree,
    const std::set<std::string>& keys);

/**
 * Pull all @ptree leaves to @leaves.
 * @ptree - source tree.
 * @parent - parent path. Not use, if ptree is all-in-one.
 * @return unique leaves collection.
 */
void pullLeaves(
    std::set<std::string>& leaves,
    const boost::property_tree::ptree& ptree,
    const std::string& parent = std::string());

/**
 * Merge @src ptree to @dest ptree.
 * @src values has priority.
 * @return result ptree object.
 */
boost::property_tree::ptree
merge(boost::property_tree::ptree dest, const boost::property_tree::ptree& src);

} // namespace config

} // namespace appkit
