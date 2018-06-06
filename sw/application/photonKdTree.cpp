#include <photonKdTree.h>

PhotonKdTree::PhotonKdTree(std::vector<photon*> *photon_map)
{
    std::vector<photon> photon_map2;

    for (std::vector<photon*>::iterator it = photon_map->begin(); it != photon_map->end(); ++it)
    {
        photon *obj = *it;
        photon_map2.push_back(*obj);
    }

	kdTree_ = new KdTree<photon, L2Norm_2, GetDim,3,float>(
            photon_map2);
}

PhotonKdTree::~PhotonKdTree()
{
}

std::vector<photon> PhotonKdTree::getKNearest(const photon &p, unsigned int m_samples_per_pixel)
{
	return kdTree_->getKNearest(p, m_samples_per_pixel);
}
