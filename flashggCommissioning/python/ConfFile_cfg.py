import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("flashggCommissioning")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(500) )

inputlist = FileUtils.loadListFromFile('/afs/cern.ch/work/f/favaro/private/miniAODforHgg/CMSSW_7_0_4/src/flashgg/MicroAODProducers/fileList_ggToH_125_13TeV.txt')
readFiles = cms.untracked.vstring( *inputlist)
process.source = cms.Source("PoolSource", fileNames = readFiles)

process.flashggPhotons = cms.EDProducer('FlashggPhotonProducer',
                                        PhotonTag=cms.untracked.InputTag('slimmedPhotons')
                                        )

process.flashggDiPhotons = cms.EDProducer('FlashggDiPhotonProducer',
                                          PhotonTag=cms.untracked.InputTag('flashggPhotons'),
                                          VertexTag=cms.untracked.InputTag('offlineSlimmedPrimaryVertices'),
                                          VertexSelectorName=cms.string("FlashggZerothVertexSelector")
                                          )

process.commissioning = cms.EDAnalyzer('flashggCommissioning',
                                       PhotonTag=cms.untracked.InputTag('flashggPhotons')
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("tree.root")
)

process.out = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('test_microAOD_ggToH_125_13TeV.root'),
                               outputCommands = cms.untracked.vstring("drop *","keep *_flashgg*_*_*","keep *_offlineSlimmedPrimaryVertices_*_*")
)


process.p = cms.Path(process.flashggPhotons*process.flashggDiPhotons*process.commissioning)
process.e = cms.EndPath(process.out)
