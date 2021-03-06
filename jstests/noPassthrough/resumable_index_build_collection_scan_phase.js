/**
 * Tests that resumable index build state is written to disk upon clean shutdown when an index
 * build is in the collection scan phase, and that the index build is subsequently completed when
 * the node is started back up.
 *
 * @tags: [
 *   requires_majority_read_concern,
 *   requires_persistence,
 *   requires_replication,
 * ]
 */
(function() {
"use strict";

load("jstests/noPassthrough/libs/index_build.js");

const dbName = "test";
const failPointName = "hangIndexBuildDuringCollectionScanPhaseBeforeInsertion";

const rst = new ReplSetTest({nodes: 1});
rst.startSet();
rst.initiate();

const coll = rst.getPrimary().getDB(dbName).getCollection(jsTestName());
assert.commandWorked(coll.insert([{a: 1}, {a: 2}]));

ResumableIndexBuildTest.run(
    rst, dbName, coll.getName(), {a: 1}, failPointName, {iteration: 0}, "collection scan", {
        numScannedAferResume: 2
    });
ResumableIndexBuildTest.run(
    rst, dbName, coll.getName(), {a: 1}, failPointName, {iteration: 1}, "collection scan", {
        numScannedAferResume: 1
    });

rst.stopSet();
})();