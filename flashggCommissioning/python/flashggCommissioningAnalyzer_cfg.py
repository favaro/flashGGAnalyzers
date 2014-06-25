import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("flashggCommissioning")

process.load("FWCore.MessageService.MessageLogger_cfi")

# geometry and global tag:

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'POSTLS170_V5::All'

#**************************************************************

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(500) )

inputlist = FileUtils.loadListFromFile('/afs/cern.ch/work/f/favaro/private/miniAODforHgg/CMSSW_7_0_4/src/flashgg/MicroAODProducers/fileList_ggToH_125_13TeV.txt')
readFiles = cms.untracked.vstring( *inputlist)
process.source = cms.Source("PoolSource", fileNames = readFiles)

#**************************************************************

process.load("flashgg/MicroAODProducers/flashggPhotons_cfi")
process.load("flashgg/MicroAODProducers/flashggDiPhotons_cfi")

process.commissioning = cms.EDAnalyzer('flashggCommissioning',
                                       PhotonTag=cms.untracked.InputTag('flashggPhotons')
)

#**************************************************************

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("tree.root")
)

process.out = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('test_microAOD_ggToH_125_13TeV.root'),
                               outputCommands = cms.untracked.vstring("drop *","keep *_flashgg*_*_*","keep *_offlineSlimmedPrimaryVertices_*_*")
)


process.p = cms.Path(process.flashggPhotons*process.flashggDiPhotons*process.commissioning)
process.e = cms.EndPath(process.out)
